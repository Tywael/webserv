#include "../inc/Loop.hpp"
#include <string>
#include <bitset>
#include <unistd.h>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

void addrProc(std::string &addr, int pos, size_t &n)
{
    std::string temp;
    int byte;

    temp = addr.substr(0, pos);
    addr.erase(0, pos + 1);
    byte = std::atoi(temp.c_str());
    if (byte >= 0 && byte < 256)
        n = (n << 8) | byte;
}

int ft_inetAddr(std::string addr)
{
    size_t n = 0;
    size_t pos;

    if (addr == "")
        return (-1);
    while((pos = addr.find(".")) != std::string::npos) {
        addrProc(addr, pos, n);
    }
    addrProc(addr, pos, n);
    n = htonl(n);
    return (n);
}

Loop::Loop(const std::vector<Server*> &tmp) : serv(tmp)
{
	FD_ZERO(&this->setfd);
	this->i = 0;
	return ;
}

Loop::Loop(const Loop & src) : serv(src.serv)
{
	*this = src;
	return ;
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Loop::~Loop()
{
	this->closesocket();
	return ;
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Loop &Loop::operator=(const Loop &rhs)
{
	if ( this != &rhs )
	{
		this->tab_socket = rhs.get_socket();
		this->tab_fd = rhs.get_fd_socket();
		this->it_socket = rhs.it_socket;
		this->sockaddr_vect = rhs.sockaddr_vect;
		this->sockaddr = rhs.sockaddr;
		this->i = rhs.i;
		this->setfd = rhs.setfd;
		this->fd_accept = rhs.fd_accept;
		this->temp_fd = rhs.temp_fd;
		this->max_fd = rhs.max_fd;
		this->temp = rhs.temp;
		this->r_octet = rhs.r_octet;
		this->w_octet = rhs.w_octet;
		this->w_buffer = rhs.w_buffer;
	}
	return (*this);
}

/*
** --------------------------------- METHODS ----------------------------------
*/

void Loop::createsocket(void)
{
	this->tab_socket.push_back(socket(AF_INET, SOCK_STREAM, 0));
	if (this->tab_socket.back() == -1)
		throw std::exception(); // temporaire
}

void Loop::setstruct(void)
{
	if (this->i < this->serv.size())
	{
		std::string c = "\033[1;34m";
		std::string nc = "\033[0m";

		std::cout << c << "Server is running..." << nc << std::endl;
		std::cout << c << "----------------------------------------------------------------" << nc << std::endl;
		std::cout << c << std::left << std::setw(18) << "Name" << nc << ": "  << this->serv[i]->getName() << std::endl;
		std::cout << c << std::left << std::setw(18) << "Host" << nc << ": " << this->serv[i]->getIp().c_str() << ":" << this->serv[i]->getPort() << std::endl;
		std::cout << c << std::left << std::setw(18) << "ft_inet_addr" << nc << ": " << ft_inetAddr(this->serv[i]->getIp().c_str()) << std::endl;
        std::cout << c << "----------------------------------------------------------------" << nc << std::endl;
		this->sockaddr.sin_port = htons(this->serv[i]->getPort());
		this->sockaddr.sin_family = AF_INET;
		this->sockaddr.sin_addr.s_addr = ft_inetAddr(this->serv[i]->getIp().c_str());
		this->sockaddr_vect.push_back(this->sockaddr);
		this->i++;
	}
}

void Loop::socksetopt(void)
{
	int temp = 1;
	if (setsockopt(this->tab_socket.back(), SOL_SOCKET, SO_REUSEADDR, &temp, sizeof(temp)) == -1)
		throw std::exception(); // temporaire
}

void Loop::socketbind(void)
{
	if (bind(this->tab_socket.back(), (struct sockaddr*)&this->sockaddr, sizeof(this->sockaddr)) == -1)
		throw std::exception(); // temporaire
}

void Loop::socketlisten(void)
{
	if (listen(this->tab_socket.back(), 1024) == -1)
		throw std::exception(); // temporaire
}

void Loop::socketaccept(void)
{
	this->tab_fd = accept(this->fd_accept, NULL, NULL);
	if (this->tab_fd == -1)
		throw std::exception(); // temporaire
}

int how_much_number(std::string temp)
{
	int ret = 0;
	int i = temp.find("Content-Length:") + 16;
	while (temp.at(i))
	{
		if (isdigit(temp.at(i)))
			ret++;
		else
			return (ret);
		i++;
	}
	return (ret);
}

void Loop::readrequete(void)
{
	std::string base;
	char *tmp;
	bool bolle = false;
	int count = 0;

	while (base.rfind("\r\n") == std::string::npos)
	{
		if (bolle == false)
		{
			tmp = new char[serv[fd_accept - this->tab_socket.front()]->getMaxBody() + 2];
			std::memset(tmp, 0, serv[fd_accept - this->tab_socket.front()]->getMaxBody() + 1);
			bolle = true;
		}
		else
		{
			tmp = new char[this->r_octet];
			std::memset(tmp, 0, this->r_octet);
		}
		this->r_octet = recv(this->tab_fd, tmp, serv[fd_accept - this->tab_socket.front()]->getMaxBody() + 1, 0);
		std::string tp(tmp, this->r_octet);
		base.append(tp);
		tp.erase();
		delete[] tmp;
		if (this->r_octet == -1)
			throw std::exception(); // temporaire
	}
	if (base.find("POST") != std::string::npos)
	{
		bolle = false;
		std::string size;

		size_t temp = base.find("\n", base.rfind("Accept-Language:")) + 3;
		count = base.size() - temp;
		size.assign(base, base.find("Content-Length:") + 16, how_much_number(base));
		int total = std::stoi(size);
		while (count < total)
		{
			if (bolle == false)
			{
				tmp = new char[serv[fd_accept - this->tab_socket.front()]->getMaxBody() + 2];
				std::memset(tmp, 0, serv[fd_accept - this->tab_socket.front()]->getMaxBody() + 1);
				bolle = true;
			}
			else
			{
				tmp = new char[total - this->r_octet];
				std::memset(tmp, 0, total - this->r_octet);
			}
			this->r_octet = recv(this->tab_fd, tmp, serv[fd_accept - this->tab_socket.front()]->getMaxBody() + 1, 0);
			std::string tp(tmp, this->r_octet);
			count += tp.size();
			base.append(tp);
			tp.erase();
			delete[] tmp;
		}
	}
	this->string_buffer = base;
}

void Loop::sendrequete(void)
{
	while (this->r_octet > 0) {
		int sent_data = send(this->tab_fd, this->w_buffer, this->r_octet, 0);
		if (sent_data < 0) {
			throw std::exception(); // handle error
		}
		this->r_octet -= sent_data;
	}
}

void Loop::closesocket(void)
{
	size_t i = 0;
	std::list<int>::iterator it = this->tab_socket.begin();
	while (i < this->tab_socket.size())
	{
		close(*it);
		it++;
		i++;
	}
	FD_ZERO(&this->setfd);
}

int Loop::getlist(int index)
{
	std::list<int>::iterator it = this->tab_socket.begin();
	int i = 0;
	while (i != index)
	{
		*it++;
		i++;
	}
	return (*it);
}

void	Loop::loop(void)
{
	HttpParser request;
	HttpParser response;

	std::string c = "\033[1;32m";
	std::string nc = "\033[0m";

	int	too_long = 0;

	try
	{
		size_t i = 0;
		while (i < this->serv.size())
		{
			this->createsocket(); // stock ici dans 1 tableau pour la suite aussi et ensuite check avec select cette plage de fd crée
			this->setstruct();
			this->socksetopt();
			this->socketbind();
			this->socketlisten();
			i++;
			std::cout << c << std::endl;
			std::cout << "New connexion" << std::endl;
			std::cout << "----------------------------------------------------------------" << nc << std::endl;
			std::cout << c << std::left << std::setw(18) << "Port" << nc << ": " << ntohs(this->sockaddr.sin_port) << std::endl;
			std::cout << c << std::left << std::setw(18) << "IP" << nc << ": " << ntohl(this->sockaddr.sin_addr.s_addr) << std::endl;
			std::cout << c << "----------------------------------------------------------------" << nc << std::endl;
		}
	}
	catch (std::exception &tmp)
	{
		std::cout << "erreur : loop initialisation (error in conf file)\n";
		return ;
	}
	i = 0;
	int it = 0;
	FD_ZERO(&this->setfd);
	
	struct timeval select_timeout;
	select_timeout.tv_sec = 3;
	select_timeout.tv_usec = 0;
	double timeout = 5;
	time_t time_before = 0;
	time_t time_after = 0;

	while (i < this->tab_socket.size())
	{
		it = getlist(i);
		if (it > this->max_fd)
			this->max_fd = it;
		FD_SET(it, &this->setfd);
		i++;
	}
	int ret = 0;
	while (ret != 1)
	{
		std::memcpy(&this->temp_fd, &this->setfd, sizeof(this->setfd));
		time_before = 0;
		time_after = 0;
		this->temp = select(this->max_fd + 1, &this->temp_fd, NULL, NULL, &select_timeout);
		time(&time_before);
		if (this->temp == -1)
			ret = 1;
		// envoie message (request)
		i = 1;
		while (i < (size_t)this->max_fd)
		{
			this->fd_accept = getlist(i);
			if (FD_ISSET(this->fd_accept, &this->temp_fd))
			{
				socketaccept();
				readrequete();
				if (r_octet > serv[fd_accept - this->tab_socket.front()]->getMaxBody()){
					too_long = 1;
				}
				else {
					too_long = 0;
				}
				// print request
				request.setServ(*serv[fd_accept - this->tab_socket.front()]);
                request.parse(this->string_buffer);
                std::cout << request;
				FD_SET(this->tab_fd, &this->temp_fd);
				break ;
			}
			i++;
		}
		// lis message (reponse)
		if (FD_ISSET(this->tab_fd, &this->temp_fd))
		{
            response = request;
			time(&time_after);
			if ((time_after - time_before) > timeout)
			{
				close(this->tab_fd);
			}
			else
			{
				response.buildResponse();
				this->w_buffer = new char[response.getBody().size() + 1];
				std::memset(w_buffer, 0, response.getBody().size() + 1);
				std::memcpy(w_buffer, response.getBody().c_str(), response.getBody().size());
				this->r_octet = response.getBody().size();
				sendrequete();
				close(this->tab_fd);
				delete[] this->w_buffer;
			}
			this->fd_accept = 0;
			this->tab_fd = 0;
			FD_ZERO(&this->temp_fd);
		}
	}
	this->closesocket();
} // src/Server.cpp:26 : segfault tous le temp;

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

const std::list<int> Loop::get_socket(void) const
{
	return (this->tab_socket);
}

const struct sockaddr_in Loop::get_sockaddr(void) const
{
	return (this->sockaddr);
}

int Loop::get_fd_socket(void) const
{
	return (this->tab_fd);
}

int Loop::get_read_octet(void)
{
	return (this->r_octet);

}

const char *Loop::get_read_buffer(void) const
{
	return (this->r_buffer);
}

int Loop::get_write_octet(void)
{
	return (this->w_octet);
}

const char *Loop::get_write_buffer(void) const
{
	return (this->w_buffer);
}

const std::vector<Server*> &Loop::get_ref_server(void) const
{
	return (this->serv);
}