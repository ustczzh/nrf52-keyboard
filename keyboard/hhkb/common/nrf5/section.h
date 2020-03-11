#ifndef SECTION_H
#define SECTION_H

/**
 * @brief 配置记录区域
 * 
 */
struct config_section_t {
    /**
     * @brief 数据长度
     * 
     */
    uint8_t len;
    /**
     * @brief 数据指针
     * 
     */
    uint8_t* data;
};

/**
 * @brief 定义一个储存区
 * 
 */
#define SECTION(section_name) NRF_SECTION_DEF(section_name, struct #section_name##_section_t)
#define SECTION_DEF(section_name,data_type) NRF_SECTION_DEF(section_name, data_type)
/**
 * @brief 定义一块数据记录区域
 * 
 */
#define SECTION_ITEM_REGISTER(section_name, item_name, item_length) NRF_SECTION_ITEM_REGISTER(section_name, struct #section_name##_section_t) item_name = { .len = item_length };
#define SECTION_ITEM_REGISTER(section_name, data_type, item_name, item_length) NRF_SECTION_ITEM_REGISTER(section_name, struct #section_name##_section_t) item_name = { .len = item_length };
#define SECTION_ITEM_COUNT(section_name) NRF_SECTION_ITEM_COUNT(section_name, struct #section_name##_section_t)
#define SECTION_ITEM_GET(section_name, i) (NRF_SECTION_ITEM_GET(section_name, struct #section_name##_section_t, i))



struct adc_channel_config {
    /**
     * @brief 通道配置
     * 
     */
    nrf_saadc_channel_config_t* config;
    /**
     * @brief ADC准备启动的事件
     * 
     */
    void (*adc_start)(void);
    /**
     * @brief ADC完毕的事件
     * 
     */
    void (*adc_finish)(nrf_saadc_value_t);
    /**
     * @brief 周期
     * 
     */
    uint16_t period;

    /**
     * @brief 计数用周期
     * 
     */
    uint16_t period_pass;
};

#define ADC_CONFIG_COUNT NRF_SECTION_ITEM_COUNT(adc_channel, struct adc_channel_config*)
#define ADC_CONFIG_GET(i) (*(NRF_SECTION_ITEM_GET(adc_channel, struct adc_channel_config*, i)))
#define ADC_CONVERT_CHANNEL(conf) NRF_SECTION_ITEM_REGISTER(adc_channel, const struct adc_channel_config* _pt_##conf) = &conf



#endif