#ifndef APPLICATION_H
#define APPLICATION_H
#include <vector>
#include <vulkan/vulkan_core.h>

#include <optional>

class Application {
  public:
    void run();

  private:
    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR        capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR>   presentModes;
    };
    struct QueueFamilyIndices {
        std::optional<unsigned int> graphicsFamily;
        std::optional<unsigned int> presentFamily;

        bool isComplete() {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

  private:
    VkInstance                 _instance;
    VkSurfaceKHR               _surface;
    VkPhysicalDevice           _physicalDevice = VK_NULL_HANDLE; // Physical device is implicitly destroyed when instance is destroyed
    VkDevice                   _device;
    VkQueue                    _graphicQueue;
    VkQueue                    _presentQueue;
    VkSwapchainKHR             _swapChain;
    VkRenderPass               _renderPass;
    VkPipelineLayout           _pipelineLayout;
    VkPipeline                 _graphicsPipeline;
    VkCommandPool              _commandPool;
    VkCommandBuffer            _commandBuffer;
    class GLFWwindow          *_window;
    std::vector<VkImage>       _swapChainImages;
    std::vector<VkImageView>   _swapChainImageViews;
    std::vector<VkFramebuffer> _swapChainFrameBuffers;
    VkFormat                   _swapChainImageFormat;
    VkExtent2D                 _swapChainExtent;
    VkSemaphore                _imageAvailableSemaphore;
    VkSemaphore                _renderFinishedSemaphore;
    VkFence                    _inFlightFence;
    void                       initVulkan();
    void                       mainLoop();
    void                       cleanup();
    void                       initWindow();
    void                       createSyncObjects();
    void                       createInstance();
    void                       createSurface();
    void                       createSwapChain();
    void                       createImageViews();
    void                       createGraphicsPipeline();
    void                       createRenderPass();
    void                       createFrameBuffer();
    void                       createCommandPool();
    void                       createCommandBuffer();
    void                       recordCommandBuffer(VkCommandBuffer, uint32_t);
    void                       drawFrame();
    void                       pickPhysicalDevice();
    void                       createLogicalDevice();
    VkSurfaceFormatKHR         chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);
    VkPresentModeKHR           chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &);
    VkExtent2D                 chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);
    VkShaderModule             createShaderModule(const std::vector<char> &);
    QueueFamilyIndices         findQueueFamilies(VkPhysicalDevice device);
    SwapChainSupportDetails    querySwapChainSupport(VkPhysicalDevice device);
    bool                       isDeviceSuitable(VkPhysicalDevice device);
    bool                       checkValidationLayerSupport();
    bool                       checkDeviceExtensionSupport(VkPhysicalDevice device);
};
#endif
