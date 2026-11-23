/**
 * @file     font_partition.h
 * @brief    字体分区检查组件 — C++ class
 *
 * 功能：字体组件（尤其整库字库）需要足够的应用分区空间，
 *       本组件提供运行时检查：当前应用分区是否达到最小要求（默认 2MB），
 *       不满足时打印错误日志并返回失败，供启动阶段自检调用。
 * 修改：2026-11-21 由 Kconfig 编译期检查重构为 FontPartitionCheck 静态类；
 *       PlatformIO 无 Kconfig，改为运行时检查 + build_flags 可覆盖阈值
 */
#ifndef FONT_PARTITION_H
#define FONT_PARTITION_H

#include <stdint.h>

/* 应用分区最小要求（KB），可用 build_flags -DFONT_PARTITION_MIN_SIZE_KB=n 覆盖 */
#ifndef FONT_PARTITION_MIN_SIZE_KB
#define FONT_PARTITION_MIN_SIZE_KB 2048 /* 2MB */
#endif

/**
 * 字体分区检查类（纯静态工具类）
 *
 * 用法：
 *   if (!FontPartitionCheck::checkAppPartition()) {
 *       // 分区不足，降级或提示
 *   }
 */
class FontPartitionCheck {
public:
    /** 应用分区最小要求（KB） */
    static constexpr uint32_t MIN_APP_SIZE_KB = FONT_PARTITION_MIN_SIZE_KB;

    /**
     * @brief  查询当前运行应用所在分区的大小
     *
     * @return 分区大小（KB）；查询失败返回 0
     */
    static uint32_t appPartitionSizeKB();

    /**
     * @brief  检查应用分区是否满足字体组件最小空间要求
     *
     * 功能：读取当前运行分区大小并与阈值比较，结果打印到日志
     *
     * @param minSizeKB 阈值（KB），传 0 使用默认 MIN_APP_SIZE_KB
     * @return true 满足；false 不足或查询失败
     */
    static bool checkAppPartition(uint32_t minSizeKB = 0);
};

#endif /* FONT_PARTITION_H */
