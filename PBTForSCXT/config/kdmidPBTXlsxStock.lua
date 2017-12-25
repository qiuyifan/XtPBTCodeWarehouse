{
	common = {
		is_log_detail = "1",
    },
	connection = {
--连接数目(多连接轮询)
		client_num = "5",
--网关地址
        gateway_address = "127.0.0.1:59903",

--数据传输是否使用ssl
		is_use_ssl = "0",
--证书文件路径
		ssl_ca_path = "../config/server.crt",
--连接超时间隔 (单位：秒，默认不填为30秒)
		conn_timeout_interval = "30",
--请求超时间隔 (单位：秒，默认不填为30秒)
		req_timeout_interval = "30",
	},
}

