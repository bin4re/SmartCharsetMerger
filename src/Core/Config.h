#pragma once

// self
#include "CharsetCode.h"
#include "LineBreaks.h"

#include <Common/tstring.h>

// third party
#include <nlohmann/json.hpp>

// standard lib
#include <unordered_set>

/**
 * @brief 配置信息
 */
struct Configuration {
    // 识别模式
    enum class DetectMode : int {
        AUTO_DETECT, // 智能识别文本文件编码
        MANUAL       // 手动指定编码（不进行自动探测）
    };

    // 文件过滤模式
    enum class FileFilterMode : int {
        NO_FILTER,   // 不过滤，处理所有文件
        BY_EXTENSION // 按后缀过滤
    };

    enum class OutputTarget { ORIGIN, TO_DIR };
    static std::unordered_set<CharsetCode> normalCharset;

    DetectMode detectMode;
    FileFilterMode fileFilterMode;
    OutputTarget outputTarget;
    std::string includeRule = u8"h hpp c cpp cxx txt";
    std::string excludeRule;
    std::string outputDir;
    CharsetCode outputCharset;
    bool enableConvertLineBreaks;
    LineBreaks lineBreak;
    std::string language;

    Configuration()
        : detectMode(DetectMode::AUTO_DETECT), fileFilterMode(FileFilterMode::NO_FILTER),
          outputTarget(OutputTarget::ORIGIN), outputCharset(CharsetCode::UTF8),
          lineBreak(LineBreaks::CRLF), enableConvertLineBreaks(false) {}

    static bool IsNormalCharset(CharsetCode charset) {
        return normalCharset.find(charset) != normalCharset.end();
    }
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Configuration, detectMode, fileFilterMode, outputTarget, includeRule,
                                   excludeRule, outputDir, outputCharset, enableConvertLineBreaks, lineBreak, language)
