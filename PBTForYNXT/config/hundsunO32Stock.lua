{
	common = {
		is_log_detail = "1",
    },
	connection = {
--������Ŀ(��������ѯ)
		client_num = "5",
--���ص�ַ
        gateway_address = "127.0.0.1:59903",

--���ݴ����Ƿ�ʹ��ssl
		is_use_ssl = "0",
--֤���ļ�·��
		ssl_ca_path = "../config/server.crt",
--���ӳ�ʱ��� (��λ���룬Ĭ�ϲ���Ϊ30��)
		conn_timeout_interval = "30",
--����ʱ��� (��λ���룬Ĭ�ϲ���Ϊ30��)
		req_timeout_interval = "30",
	},
}

