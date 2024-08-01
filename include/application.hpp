#ifndef APPLICATION_H
#define APPLICATION_H
#include <optional>
#include <vulkan/vulkan_core.h>

class Application {
public:
  void run();

private:
  VkInstance instance;
  VkPhysicalDevice physicalDevice =
      VK_NULL_HANDLE; // Physical device is implicitly destroyed when instance
                      // is destroyed
  class GLFWwindow *window;
  struct QueueFamilyIndices {
    std::optional<unsigned int> graphicsFamily;
  };

  void initVulkan();
  void mainLoop();
  void cleanup();
  void initWindow();
  void createInstance();
  void pickPhysicalDevice();
  QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

  bool isDeviceSuitable(VkPhysicalDevice device);
  bool checkValidationLayerSupport();
};
#endif
