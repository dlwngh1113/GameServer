#include "CUser.h"

UserState CUser::GetUserState() const
{
    return m_userState;
}

void CUser::InitIO()
{
	DWORD flags = 0;
	int ret;
	m_ioLock.lock();
	ret = WSARecv(m_sock, &m_recv_over.wsa_buf, 1, NULL, &flags, &m_recv_over.wsa_over, NULL);
	m_ioLock.unlock();
	
	if (SOCKET_ERROR == ret) 
	{
		int err_no = WSAGetLastError();
		if (ERROR_IO_PENDING != err_no)
			std::cout << "WSARecv: " << err_no << std::endl;
		//error_display("WSARecv : ", err_no);
	}
}
