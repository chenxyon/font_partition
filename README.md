# Font Partition 组件 v1.0（C++ class 版）

## 简介

字体分区检查组件。字体组件（尤其整库字库）需要足够的应用分区空间，本组件在运行时检查当前应用分区是否达到最小要求（默认 2MB），供启动阶段自检调用。

原实现为 ESP-IDF Kconfig 编译期检查；PlatformIO 无 Kconfig，重构为运行时检查类。

## 文件结构

```
font_partition/
├── font_partition.h    # FontPartitionCheck 静态类声明
├── font_partition.cpp  # 分区检查实现
├── library.json        # PlatformIO 库描述
└── README.md
```

## API 参考

```cpp
#include "font_partition.h"

/* 启动自检：分区不足会打印错误日志并返回 false */
if (!FontPartitionCheck::checkAppPartition()) {
    // 分区不足：降级（少字库模式）或提示用户更换分区表
}

/* 也可指定自定义阈值（KB） */
FontPartitionCheck::checkAppPartition(4096);

/* 仅查询当前应用分区大小（KB），失败返回 0 */
uint32_t sizeKB = FontPartitionCheck::appPartitionSizeKB();
```

## 配置

| 宏 | 默认值 | 说明 |
|----|--------|------|
| `FONT_PARTITION_MIN_SIZE_KB` | 2048 | 应用分区最小要求（KB），可在 platformio.ini 的 `build_flags` 中覆盖 |

## 版本历史

| 版本 | 日期 | 说明 |
|------|------|------|
| v1.0.0 | 2026-11-21 | 由 Kconfig 编译期检查重构为 FontPartitionCheck 运行时检查类 |

## 许可证

MIT License
