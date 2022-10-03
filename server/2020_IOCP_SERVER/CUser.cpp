#include "CUser.h"

UserState CUser::GetUserState() const
{
    return m_userState;
}

void CUser::InitIO()
{
	DWORD flags = 0;
	int ret;
	this->GetInfo()->c_lock.lock();
	ret = WSARecv(this->m_sock, &this->m_recv_over.wsa_buf, 1, NULL,
		&flags, &this->m_recv_over.wsa_over, NULL);
	this->GetInfo()->c_lock.unlock();
	if (SOCKET_ERROR == ret) {
		int err_no = WSAGetLastError();
		if (ERROR_IO_PENDING != err_no)
			std::cout << "WSARecv: " << err_no << std::endl;
		//error_display("WSARecv : ", err_no);
	}
}
