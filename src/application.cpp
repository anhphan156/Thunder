#include "application.hpp"

#include <cstring>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <vector>

const uint32_t WIDTH  = 800;
const uint32_t HEIGHT = 600;

void on_err(int err, const char *desc) {
    std::cout << desc << std::endl;
}

const std::vector<const char *> validationLayers = {"VK_LAYER_KHRONOS_validation"};

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

void Application::run() {
    initWindow();
    initVulkan();
    mainLoop();
    cleanup();
}

void Application::initVulkan() {
    createInstance();
    pickPhysicalDevice();
}

void Application::mainLoop() {
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }
}

void Application::cleanup() {
    vkDestroyInstance(instance, nullptr);
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Application::initWindow() {
    if (!glfwInit()) {
        std::cout << "GLFW init failed\n";
    }

    glfwSetErrorCallback(on_err);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    /*glfwWindowHint(GLFW_PLATFORM, GLFW_PLATFORM_WAYLAND);*/

    window = glfwCreateWindow(WIDTH, HEIGHT, "GLFW", nullptr, nullptr);
}

void Application::createInstance() {
    if (enableValidationLayers && !checkValidationLayerSupport()) {
        throw std::runtime_error("validation layer requested but not available");
    }

    VkApplicationInfo appInfo{};
    appInfo.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName   = "Vulkan Tutorial";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName        = "No Engine";
    appInfo.engineVersion      = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion         = VK_API_VERSION_1_0;

    uint32_t     glfwExtensionCount = 0;
    const char **glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    VkInstanceCreateInfo createInfo{};
    createInfo.sType                   = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo        = &appInfo;
    createInfo.enabledExtensionCount   = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;
    if (enableValidationLayers) {
        createInfo.enabledLayerCount   = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
    } else {
        createInfo.enabledLayerCount = 0;
    }

    VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
    if (result != VK_SUCCESS) {
        throw std::runtime_error("failed to create instance");
    }
}

void Application::pickPhysicalDevice() {
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
    if (deviceCount == 0) {
        throw std::runtime_error("failed to find gpus with vulkan support");
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

    for (const auto &device : devices) {
        if (isDeviceSuitable(device)) {
            physicalDevice = device;
            break;
        }
    }

    if (physicalDevice == VK_NULL_HANDLE) {
        throw std::runtime_error("failed to find a suitable gpu");
    }
}
Application::QueueFamilyIndices Application::findQueueFamilies(VkPhysicalDevice device) {
    QueueFamilyIndices indices;

    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    int i = 0;
    for (const auto &queueFamily : queueFamilies) {
        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            indices.graphicsFamily = i++;
        }

        if (indices.graphicsFamily.has_value())
            break;
    }

    return indices;
}

bool Application::isDeviceSuitable(VkPhysicalDevice device) {
    /*VkPhysicalDeviceFeatures deviceFeatures;*/
    /*VkPhysicalDeviceProperties deviceProperties;*/
    /*vkGetPhysicalDeviceFeatures(device, &deviceFeatures);*/
    /*vkGetPhysicalDeviceProperties(device, &deviceProperties);*/
    QueueFamilyIndices indices = findQueueFamilies(device);

    return indices.graphicsFamily.has_value();
}

bool Application::checkValidationLayerSupport() {
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for (const char *layername : validationLayers) {
        for (const auto &layerProperties : availableLayers) {
            if (strcmp(layername, layerProperties.layerName) == 0) {
                return true;
            }
        }
    }

    return false;
}
