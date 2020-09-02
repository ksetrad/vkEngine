//
// Created by Владимир on 31.08.2020.
//

#include "tools/vk/swapChain.h"
#include "tools/configuration.h"

using namespace vk;

SwapChain::SwapChain (
        Instance * instance ,
        PhysicalDevice * physicalDevice ,
        LogicalDevice * logicalDevice
                     ): logicalDevice(logicalDevice)
{
        Surface::Details details = instance->getSurface ()->getSwapChainDetails (
                physicalDevice->getPhysicalDevice () );

        /// Вычисляем параметры
        surfaceFormat = chooseSwapSurfaceFormat ( details.formats );
        VkPresentModeKHR presentMode = chooseSwapPresentMode ( details.presentModes );
        extent = chooseSwapExtent ( details.capabilities );

        /// Вычисляем количество кадров в цепочке переключения кадров
        uint32_t imageCount = details.capabilities.minImageCount + 1;
        if ( details.capabilities.maxImageCount > 0 &&
             imageCount > details.capabilities.maxImageCount )
        {
                imageCount = details.capabilities.maxImageCount;
        }

        VkSwapchainCreateInfoKHR createInfo { };
        createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        /// Устанавливаем используемую поверхность отрисовки
        createInfo.surface = instance->getSurface ()->getSurface ();

        /// Устанавливаем количество кадров
        createInfo.minImageCount = imageCount;
        /// Устанваливаем формат цвета пикселя
        createInfo.imageFormat = surfaceFormat.format;
        /// Устанавливаем формат цветового пространства
        createInfo.imageColorSpace = surfaceFormat.colorSpace;
        /// Устанавилваем размер
        createInfo.imageExtent = extent;
        /// Мы не разрабатываем виртуальную реальность поэтому изображение состоит из одного слоя
        createInfo.imageArrayLayers = 1;
        /// Изображение используется без постобработки (если нужна пост обработка флаг VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT)
        createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

        /// Получаем индексы очередей
        auto indices = physicalDevice->getIndices ();
        uint32_t queueFamilyIndices[] = { indices.graphicsFamily.value () , indices.presentFamily.value () };

        /// Если разные семейства очередей используются для графики и презентации
        if ( indices.graphicsFamily != indices.presentFamily )
        {
                /// ТО используем конкурентный режим доступа к изображению
                createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
                createInfo.queueFamilyIndexCount = 2;
                createInfo.pQueueFamilyIndices = queueFamilyIndices;
        }
        else
        {
                /// Иначе режим эксклюзивный
                createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        }

        /// НЕ используем предварительного изменения изображения
        createInfo.preTransform = details.capabilities.currentTransform;

        /// Флаг того что альфа канал не предназначен для смешивания с другими окнами в оконной системе
        createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        createInfo.presentMode = presentMode;
        /// Флаг того что отрезанные пиксели не нужны
        createInfo.clipped = VK_TRUE;
        /// TODO старой цепочки кадров нет (при измении размера окна этот параметр должен измениться)
        createInfo.oldSwapchain = VK_NULL_HANDLE;

        /// Создаем цепочку смены кадров
        if ( vkCreateSwapchainKHR ( logicalDevice->getDevice () , & createInfo , nullptr , & swapChain ) != VK_SUCCESS )
        {
                throw vulkan_exception( "failed to create swap chain!" );
        }

        /// Формируем массив для хранения изображений цепочки смены кадров
        vkGetSwapchainImagesKHR ( logicalDevice->getDevice () , swapChain , & imageCount , nullptr );
        swapChainImages.resize ( imageCount );
        vkGetSwapchainImagesKHR ( logicalDevice->getDevice () , swapChain , & imageCount , swapChainImages.data () );

        /// Формируем массив для хранения представлений изображений цепочки смены кадров
        swapChainImagesView.resize(swapChainImages.size());
        for (size_t i = 0; i < swapChainImages.size(); i++) {
                VkImageViewCreateInfo imageViewCreateInfo{};
                imageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
                /// Устанавливаем изображение для которого формируется представление
                imageViewCreateInfo.image = swapChainImages[i];

                /// Устанавливаем формат изображения (формат пикселя и тип изображения)
                imageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
                imageViewCreateInfo.format = surfaceFormat.format;

                /// Для каждого компонента пикселя устанавливается его соответствующий цветовой компонент
                imageViewCreateInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
                imageViewCreateInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
                imageViewCreateInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
                imageViewCreateInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

                /// Изображение используется как представление цвета
                imageViewCreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
                /// Базовый уровень мипмапов
                imageViewCreateInfo.subresourceRange.baseMipLevel = 0;
                /// число мип мапов
                imageViewCreateInfo.subresourceRange.levelCount = 1;
                /// Базовый уровень слоев (не используется)
                imageViewCreateInfo.subresourceRange.baseArrayLayer = 0;
                /// число слоев
                imageViewCreateInfo.subresourceRange.layerCount = 1;

                /// Формируем представление изображения
                if ( vkCreateImageView( logicalDevice->getDevice(), &imageViewCreateInfo, nullptr, &swapChainImagesView[i]) != VK_SUCCESS) {
                        throw vulkan_exception("failed to create image views!");
                }
        }

}

VkSurfaceFormatKHR
SwapChain::chooseSwapSurfaceFormat ( const std::vector < VkSurfaceFormatKHR > & availableFormats )
{

        for ( const auto & availableFormat : availableFormats )
        {
                if ( availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB &&
                     availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR )
                {
                        return availableFormat;
                }
        }
        return availableFormats[ 0 ];

}

VkPresentModeKHR
SwapChain::chooseSwapPresentMode ( const std::vector < VkPresentModeKHR > & availablePresentModes )
{
        for ( const auto & availablePresentMode : availablePresentModes )
        {
                if ( availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR )
                {
                        return availablePresentMode;
                }
        }

        return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D
SwapChain::chooseSwapExtent ( const VkSurfaceCapabilitiesKHR & capabilities )
{
        if ( capabilities.currentExtent.width != UINT32_MAX )
        {
                return capabilities.currentExtent;
        }
        else
        {
                VkExtent2D actualExtent = {
                        static_cast<uint32_t>(Configuration::display ().resolution.width) ,
                        static_cast<uint32_t>(Configuration::display ().resolution.height)
                };

                actualExtent.width = std::max ( capabilities.minImageExtent.width ,
                                                std::min ( capabilities.maxImageExtent.width , actualExtent.width ) );
                actualExtent.height = std::max ( capabilities.minImageExtent.height ,
                                                 std::min ( capabilities.maxImageExtent.height ,
                                                            actualExtent.height ) );

                return actualExtent;
        }
}

SwapChain::~SwapChain ()
{
        /// Разрушаем представления изображений
        for (auto imageView : swapChainImagesView) {
                vkDestroyImageView(logicalDevice->getDevice(), imageView, nullptr);
        }
        /// Разрушаем цепочку смены кадров
        vkDestroySwapchainKHR(logicalDevice->getDevice(), swapChain, nullptr);
}
