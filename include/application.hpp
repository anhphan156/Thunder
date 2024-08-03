#ifndef APPLICATION_H
#define APPLICATION_H
#include <vulkan/vulkan_core.h>

#include <optional>

class Application {
  public:
    void run();

  private:
    struct QueueFamilyIndices {
        std::optional<unsigned int> graphicsFamily;
    };

  private:
    VkInstance         instance;
    VkPhysicalDevice   physicalDevice = VK_NULL_HANDLE; // Physical device is implicitly destroyed when instance is destroyed
    VkDevice           device;
    VkQueue            graphicQueue;
    class GLFWwindow  *window;
    void               initVulkan();
    void               mainLoop();
    void               cleanup();
    void               initWindow();
    void               createInstance();
    void               pickPhysicalDevice();
    void               createLogicalDevice();
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
    bool               isDeviceSuitable(VkPhysicalDevice device);
    bool               checkValidationLayerSupport();
};
#endif
