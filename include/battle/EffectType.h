#ifndef EFFECTTYPE_H
#define EFFECTTYPE_H

// 技能效果类型枚举
enum class EffectType {
    Normal,       // 普通效果（加减固定数值）
    Percentage,   // 百分比效果（加减百分比）
    Status        // 特殊状态（如眩晕、中毒等）
};

#endif