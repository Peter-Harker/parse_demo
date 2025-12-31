// 引入 parser 模块的头文件，才能调用解析函数
#include "parser/parser.h"

// 主函数：程序入口
int main() {
    // 1. 定义测试用例（待解析的字符串，支持多个测试）
    const char *test_input1 = "username=zhengjiayang";  // 合法格式
    const char *test_input2 = "password=123456";    // 合法格式
    const char *test_input3 = "no_equal_sign";      // 无效格式（无=）
    const char *test_input4 = "";                   // 空字符串

    // 2. 定义 KeyValuePair 变量，用于存储解析结果
    KeyValuePair result;
    // 初始化结构体成员（避免野指针）
    result.key = NULL;
    result.value = NULL;

    // 3. 测试解析功能（以 test_input1 为例，可替换为其他测试用例）
    ParseStatus status = parse_key_value(test_input1, &result);

    // 4. 根据解析状态，输出对应信息
    switch (status) {
        case PARSE_SUCCESS:
            printf("解析成功！\n");
            printf("键（key）：%s\n", result.key);
            printf("值（value）：%s\n", result.value);
            break;
        case PARSE_EMPTY:
            printf("解析失败：待解析字符串为空！\n");
            break;
        case PARSE_INVALID:
            printf("解析失败：字符串格式无效（需满足 key=value 格式）！\n");
            break;
        case PARSE_MEM_ERROR:
            printf("解析失败：内存分配失败！\n");
            break;
        default:
            printf("解析失败：未知错误！\n");
            break;
    }

    // 5. 释放解析结果的动态内存，防止内存泄漏（必须调用）
    free_key_value(&result);

    // 6. 程序正常退出
    return 0;
}
