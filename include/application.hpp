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
    VkInstance               _instance;
    VkSurfaceKHR             _surface;
    VkPhysicalDevice         _physicalDevice = VK_NULL_HANDLE; // Physical device is implicitly destroyed when instance is destroyed
    VkDevice                 _device;
    VkQueue                  _graphicQueue;
    VkQueue                  _presentQueue;
    VkSwapchainKHR           _swapChain;
    class GLFWwindow        *_window;
    std::vector<VkImage>     _swapChainImages;
    std::vector<VkImageView> _swapChainImageViews;
    VkFormat                 _swapChainImageFormat;
    VkExtent2D               _swapChainExtent;
    void                     initVulkan();
    void                     mainLoop();
    void                     cleanup();
    void                     initWindow();
    void                     createInstance();
    void                     createSurface();
    void                     createSwapChain();
    void                     createImageViews();
    void                     pickPhysicalDevice();
    void                     createLogicalDevice();
    VkSurfaceFormatKHR       chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);
    VkPresentModeKHR         chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &);
    VkExtent2D               chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);
    QueueFamilyIndices       findQueueFamilies(VkPhysicalDevice device);
    SwapChainSupportDetails  querySwapChainSupport(VkPhysicalDevice device);
    bool                     isDeviceSuitable(VkPhysicalDevice device);
    bool                     checkValidationLayerSupport();
    bool                     checkDeviceExtensionSupport(VkPhysicalDevice device);
};
#endif
