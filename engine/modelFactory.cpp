//
// Created by Владимир on 12.09.2020.
//
#include <fstream>
#include "tools/configuration.h"
#include "modelFactory.h"

using namespace engine;

ModelFactory::ModelFactory (
        vk::Core * core ,
        vk::CommandPool * commandPool
                           )
        : core ( core ) , commandPool ( commandPool )
{

}

Model*
ModelFactory::openModel ( const std::string & path )
{
        std::string folder = Configuration::engine ().modelDirPath;
        std::ifstream stream = std::ifstream { folder + path , std::ios::binary };

        //TODO учет ошибок загрузки stream.exceptions(std::ios_base::badbit);
        std::vector < vk::Vertex > vertexes;
        std::vector < unsigned int > indices;

        uint64_t vertSize , indSize;
        if ( stream.is_open () )
        {
                uint32_t version;
                stream.read ( reinterpret_cast<char *>(& version) , 4 );
                if ( version == 1 )
                {
                        stream.read ( reinterpret_cast<char *>(& vertSize) , 8 );
                        stream.read ( reinterpret_cast<char *>(& indSize) , 8 );
                        vertexes.resize ( vertSize );
                        indices.resize ( indSize );
                        stream.read ( reinterpret_cast<char *>(vertexes.data ()) , vertSize * sizeof ( vk::Vertex ) );
                        stream.read ( reinterpret_cast<char *>(indices.data ()) , indSize * sizeof ( unsigned int) );
                }
        }
        auto model = new Model ( core , vertexes , indices );
        commandPool->cmdTransferBuffer ( model->vbo );
        commandPool->cmdTransferBuffer ( model->ibo );
        return model;
}

