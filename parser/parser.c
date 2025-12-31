// 引入本模块的头文件，关联函数声明
#include "parser.h"

// 实现核心解析函数：parse_key_value
ParseStatus parse_key_value(const char *input_str, KeyValuePair *result) {
    // 步骤1：合法性校验 - 输入字符串或结果指针为空，直接返回无效
    if (input_str == NULL || result == NULL) {
        return PARSE_INVALID;
    }

    // 步骤2：检查输入字符串是否为空字符串（长度为0）
    if (strlen(input_str) == 0) {
        return PARSE_EMPTY;
    }

    // 步骤3：查找分隔符 '=' 的位置（核心解析逻辑）
    const char *equal_sign = strchr(input_str, '=');
    if (equal_sign == NULL) {
        return PARSE_INVALID;  // 未找到 '='，格式不合法
    }

    // 步骤4：计算键（key）和值（value）的长度
    size_t key_len = equal_sign - input_str;  // 键的长度：从字符串开头到 '='
    size_t value_len = strlen(input_str) - key_len - 1;  // 值的长度：总长度 - 键长度 - 1（排除 '='）

    // 校验键或值是否为空（长度为0），无效格式
    if (key_len == 0 || value_len == 0) {
        return PARSE_INVALID;
    }

    // 步骤5：为键（key）动态分配内存并拷贝内容
    result->key = (char *)malloc(key_len + 1);  // +1 用于存储字符串结束符 '\0'
    if (result->key == NULL) {
        return PARSE_MEM_ERROR;  // 内存分配失败
    }
    strncpy(result->key, input_str, key_len);  // 拷贝键的内容
    result->key[key_len] = '\0';  // 手动添加字符串结束符，确保字符串有效性

    // 步骤6：为值（value）动态分配内存并拷贝内容
    result->value = (char *)malloc(value_len + 1);
    if (result->value == NULL) {
        // 若值的内存分配失败，需释放已分配的键内存，防止内存泄漏
        free(result->key);
        result->key = NULL;
        return PARSE_MEM_ERROR;
    }
    strncpy(result->value, equal_sign + 1, value_len);  // 拷贝值的内容（从 '=' 后一位开始）
    result->value[value_len] = '\0';  // 手动添加字符串结束符

    // 步骤7：所有步骤执行完成，解析成功
    return PARSE_SUCCESS;
}

// 实现辅助函数：释放 KeyValuePair 的动态内存
void free_key_value(KeyValuePair *kv_pair) {
    if (kv_pair == NULL) {
        return;  // 入参为空，直接返回
    }
    // 释放键的内存
    if (kv_pair->key != NULL) {
        free(kv_pair->key);
        kv_pair->key = NULL;  // 置空，防止野指针
    }
    // 释放值的内存
    if (kv_pair->value != NULL) {
        free(kv_pair->value);
        kv_pair->value = NULL;  // 置空，防止野指针
    }
}
// 新增：代码行统计函数实现
ParseStatus count_file_lines(const char *file_path, int *line_count) {
    // 1. 合法性校验：参数为空直接返回无效
    if (file_path == NULL || line_count == NULL) {
        return PARSE_INVALID;
    }

    // 2. 初始化统计结果为0
    *line_count = 0;

    // 3. 只读模式打开文件，判断是否打开成功
    FILE *fp = fopen(file_path, "r");
    if (fp == NULL) {
        return PARSE_INVALID; // 文件不存在/权限问题，返回无效
    }

    // 4. 逐行读取文件，过滤空行并统计
    char buffer[1024]; // 存储每行内容，支持最长1023个字符
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        // 去除行首空白字符（空格、制表符、换行符、回车符）
        char *trimmed = buffer;
        while (*trimmed == ' ' || *trimmed == '\t' || *trimmed == '\n' || *trimmed == '\r') {
            trimmed++;
        }
        // 去除空白后为空，视为纯空行，不统计
        if (*trimmed == '\0') {
            continue;
        }
        // 有效行，计数+1
        (*line_count)++;
    }

    // 5. 关闭文件，释放资源（避免内存泄漏）
    fclose(fp);

    // 6. 统计成功，返回成功状态
    return PARSE_SUCCESS;
}
