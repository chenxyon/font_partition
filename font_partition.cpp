/**
 * @file     font_partition.cpp
 * @brief    字体分区检查组件实现 — C++ class
 *
 * 功能：运行时检查当前应用分区大小是否满足字体组件最小空间要求
 * 修改：2026-11-21 由 Kconfig 编译期检查重构为 FontPartitionCheck 静态类
 */
#include "font_partition.h"

#include "esp_log.h"
#include "esp_partition.h"

static const char *TAG = "font_partition";

uint32_t FontPartitionCheck::appPartitionSizeKB()
{
    /* 取当前正在运行的应用分区（OTA 场景下即实际运行分区） */
    const esp_partition_t *part = esp_partition_get_running();
    if (part == NULL) {
        /* 兜底：按类型查找第一个应用分区 */
        part = esp_partition_find_first(ESP_PARTITION_TYPE_APP, ESP_PARTITION_SUBTYPE_ANY, NULL);
    }
    if (part == NULL) {
        ESP_LOGE(TAG, "未找到应用分区");
        return 0;
    }
    return (uint32_t)(part->size / 1024);
}

bool FontPartitionCheck::checkAppPartition(uint32_t minSizeKB)
{
    if (minSizeKB == 0) {
        minSizeKB = MIN_APP_SIZE_KB;
    }

    uint32_t sizeKB = appPartitionSizeKB();
    if (sizeKB == 0) {
        ESP_LOGE(TAG, "分区大小查询失败，无法校验（要求 >= %lu KB）", (unsigned long)minSizeKB);
        return false;
    }

    if (sizeKB < minSizeKB) {
        ESP_LOGE(TAG, "应用分区不足：当前 %lu KB < 要求 %lu KB，字体功能可能无法使用",
                 (unsigned long)sizeKB, (unsigned long)minSizeKB);
        return false;
    }

    ESP_LOGI(TAG, "分区检查通过：当前 %lu KB >= 要求 %lu KB",
             (unsigned long)sizeKB, (unsigned long)minSizeKB);
    return true;
}

#include "font_partition_version.h"
#include "version_manager.h"
COMPONENT_VERSION_REGISTER(font_partition, FONT_PARTITION_VERSION_STRING)
