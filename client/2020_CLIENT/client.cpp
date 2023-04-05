#include"CMapLoader.h"
using namespace std;
using namespace chrono;

sf::TcpSocket g_socket;

constexpr auto TILE_WIDTH = 32;
constexpr auto CLIENT_WIDTH = 20;
constexpr auto CLIENT_HEIGHT = 20;
constexpr auto BUF_SIZE = 200;

int g_left_x;
int g_top_y;
int g_myid;

sf::RenderWindow* g_window;
sf::Font g_font;

class OBJECT {
private:
	bool m_showing;
	sf::Sprite m_sprite;

	char m_mess[MAX_STR_LEN];
	high_resolution_clock::time_point m_time_out;
	sf::Text m_text;
	sf::Text m_name;	

public:
	short m_x{ 0 }, m_y{ 0 };
	short hp{ 0 };
	short level{ 0 };
	int   exp{ 0 };
	char name[MAX_ID_LEN];
	OBJECT(sf::Texture& t, int x, int y, int x2, int y2) {
		m_showing = false;
		m_sprite.setTexture(t);
		m_sprite.setTextureRect(sf::IntRect(x, y, x2, y2));
		m_time_out = high_resolution_clock::now();
	}
	OBJECT() {
		m_showing = false;
		m_time_out = high_resolution_clock::now();
	}
	void show()
	{
		m_showing = true;
	}
	void hide()
	{
		m_showing = false;
	}

	void a_move(short x, short y) {
		m_sprite.setPosition((float)x, (float)y);
	}

	void a_draw() {
		g_window->draw(m_sprite);
	}

	void move(short x, short y) {
		m_x = x;
		m_y = y;
	}
	void draw() {
		if (false == m_showing) return;
		float rx = (m_x - g_left_x) * TILE_WIDTH + 8;
		float ry = (m_y - g_top_y) * TILE_WIDTH + 8;
		m_sprite.setPosition(rx, ry);
		g_window->draw(m_sprite);
		m_name.setPosition(rx - 10, ry - 10);
		g_window->draw(m_name);
		if (high_resolution_clock::now() < m_time_out) {
			m_text.setPosition(rx - 10, ry + 10);
			g_window->draw(m_text);
		}
	}
	void set_name(char str[]) {
		m_name.setFont(g_font);
		m_name.setCharacterSize(15);
		m_name.setString(str);
		m_name.setFillColor(sf::Color(255, 255, 0));
		m_name.setStyle(sf::Text::Bold);
	}
	void add_chat(char chat[]) {
		m_text.setFont(g_font);
		m_text.setString(chat);
		m_text.setCharacterSize(15);
		m_time_out = high_resolution_clock::now() + 1s;
	}
};

OBJECT avatar;
unordered_map <int, OBJECT> npcs;
vector<sf::Text> g_chatLog;

OBJECT tile1;
OBJECT tile2;
OBJECT tile3;
OBJECT ghost;

short g_map[WORLD_WIDTH][WORLD_HEIGHT];

sf::Texture* board;
sf::Texture* pieces;
sf::Texture* ghost_img;

void send_packet(void* packet);

void client_initialize()
{
	board = new sf::Texture;
	pieces = new sf::Texture;
	ghost_img = new sf::Texture;
	CMapLoader::LoadMap(g_map, "map.txt");
	if (false == g_font.loadFromFile("Resources/cour.ttf")) {
		cout << "Font Loading Error!\n";
		while (true);
	}
	board->loadFromFile("Resources/maptile.png");
	pieces->loadFromFile("Resources/players.png");
	ghost_img->loadFromFile("Resources/ghost.png");
	tile1 = OBJECT{ *board, 0, 0, TILE_WIDTH, TILE_WIDTH };
	tile2 = OBJECT{ *board, 32, 0, TILE_WIDTH, TILE_WIDTH };
	tile3 = OBJECT{ *board, 64, 0, TILE_WIDTH, TILE_WIDTH };
	ghost = OBJECT{ *ghost_img, 0, 0, TILE_WIDTH, TILE_WIDTH };
	avatar = OBJECT{ *pieces, 0, 0, TILE_WIDTH, TILE_WIDTH };
	avatar.move(4, 4);
}

void client_finish()
{
	delete board;
	delete pieces;
	delete ghost_img;
}

void ProcessPacket(char* ptr)
{
	switch (ptr[1])
	{
	case SC_PACKET_LOGIN_OK:
	{
		LoginResponse* packet = reinterpret_cast<LoginResponse*>(ptr);
		g_myid = packet->id;
		avatar.move(packet->x, packet->y);
		avatar.hp = packet->hp;
		avatar.level = packet->level;
		avatar.exp = packet->exp;
		//g_left_x = packet->x - CLIENT_WIDTH / 2;
		//g_top_y = packet->y - CLIENT_HEIGHT / 2;
		//printf("%d %d %d %d %d %d\n",
		//	my_packet->id,
		//	my_packet->hp,
		//	my_packet->exp,
		//	my_packet->level,
		//	avatar.m_x,
		//	avatar.m_y);
		avatar.show();

		PlaceEnterRequest p_packet;
		p_packet.size = sizeof(p_packet);
		p_packet.type = CS_ENTERPLACE;
		p_packet.placeId = 0;

		send_packet(&p_packet);
	}
	break;
	case SC_PACKET_LOGIN_FAIL:
	{
		LoginFailResponse* packet = reinterpret_cast<LoginFailResponse*>(ptr);
		cout << packet->message << endl;
		cout << "제대로 된 아이디를 입력해주십시오:";
		string s;
		cin >> s;

		LoginRequest l_packet;
		l_packet.size = sizeof(l_packet);
		l_packet.type = CS_LOGIN;
		int t_id = GetCurrentProcessId();
		sprintf_s(l_packet.name, s.c_str());
		strcpy_s(avatar.name, l_packet.name);
		avatar.set_name(l_packet.name);
		send_packet(&l_packet);
	}
	break;
	case SC_PACKET_ENTER:
	{
		UserEnterEvent* packet = reinterpret_cast<UserEnterEvent*>(ptr);
		int id = packet->id;

		avatar.move(packet->x, packet->y);
		g_left_x = packet->x - CLIENT_WIDTH / 2;
		g_top_y = packet->y - CLIENT_HEIGHT / 2;
		avatar.show();
	}
	break;
	case SC_OtherUserEnter:
	{
		UserEnterEvent* packet = reinterpret_cast<UserEnterEvent*>(ptr);
		int id = packet->id;

		if (id < MAX_USER)
			npcs[id] = OBJECT{ *pieces, 0, 0, TILE_WIDTH, TILE_WIDTH };
		else
			npcs[id] = OBJECT{ *pieces, 32, 0, TILE_WIDTH, TILE_WIDTH };
		strcpy_s(npcs[id].name, packet->name);
		npcs[id].set_name(packet->name);
		npcs[id].move(packet->x, packet->y);
		npcs[id].show();
	}
	break;
	case SC_PACKET_MOVE:
	{
		MoveResponse* packet = reinterpret_cast<MoveResponse*>(ptr);
		int other_id = packet->id;
		if (other_id == g_myid) {
			avatar.move(packet->x, packet->y);
			g_left_x = packet->x - CLIENT_WIDTH / 2;
			g_top_y = packet->y - CLIENT_HEIGHT / 2;
		}
		else {
			if (0 != npcs.count(other_id))
				npcs[other_id].move(packet->x, packet->y);
		}
	}
	break;
	case SC_PACKET_EXIT:
	{
		UserExitEvent* my_packet = reinterpret_cast<UserExitEvent*>(ptr);
		int other_id = my_packet->id;
		if (other_id == g_myid) {
			avatar.hide();
		}
		else {
			if (0 != npcs.count(other_id))
				npcs[other_id].hide();
		}
	}
	break;
	case SC_PACKET_CHAT:
	{
		ChattingEvent* my_packet = reinterpret_cast<ChattingEvent*>(ptr);
		int other_id = my_packet->id;
		if (g_myid != other_id)
			npcs[other_id].add_chat(my_packet->message);
		else {
			sf::Text tmp;
			char buf[MAX_STR_LEN];
			tmp.setFont(g_font);
			strcpy_s(buf, my_packet->message);
			tmp.setString(buf);
			tmp.setCharacterSize(20);
			g_chatLog.push_back(tmp);
			if (g_chatLog.size() > 3)
				g_chatLog.erase(g_chatLog.begin());
		}
	}
	break;
	case SC_PACKET_STAT_CHANGE:
	{
		StatusChangedEvent* p = reinterpret_cast<StatusChangedEvent*>(ptr);
		//printf("avatar level = %hd exp = %d hp = %hd, packet level = %hd exp = %d hp = %hd\n", 
		//	avatar.level, avatar.exp, avatar.hp, p->level, p->exp, p->hp);
		avatar.level = p->level;
		avatar.exp = p->exp;
		avatar.hp = p->hp;
		printf("avatar level = %hd exp = %d hp = %hd, packet level = %hd exp = %d hp = %hd\n",
			avatar.level, avatar.exp, avatar.hp, p->level, p->exp, p->hp);
	}
	break;
	default:
		printf("Unknown PACKET type [%d]\n", ptr[1]);
		break;
	}
}

void process_data(char* net_buf, size_t io_byte)
{
	char* ptr = net_buf;
	static size_t in_packet_size = 0;
	static size_t saved_packet_size = 0;
	static char packet_buffer[BUF_SIZE];

	while (0 != io_byte) {
		if (0 == in_packet_size) in_packet_size = ptr[0];
		if (io_byte + saved_packet_size >= in_packet_size) {
			memcpy(packet_buffer + saved_packet_size, ptr, in_packet_size - saved_packet_size);
			ProcessPacket(packet_buffer);
			ptr += in_packet_size - saved_packet_size;
			io_byte -= in_packet_size - saved_packet_size;
			in_packet_size = 0;
			saved_packet_size = 0;
		}
		else {
			memcpy(packet_buffer + saved_packet_size, ptr, io_byte);
			saved_packet_size += io_byte;
			io_byte = 0;
		}
	}
}

void client_main()
{
	char net_buf[BUF_SIZE];
	size_t	received;

	auto recv_result = g_socket.receive(net_buf, BUF_SIZE, received);
	if (recv_result == sf::Socket::Error)
	{
		wcout << L"Recv 에러!";
		while (true);
	}

	if (recv_result == sf::Socket::Disconnected)
	{
		wcout << L"서버 접속 종료.";
		g_window->close();
	}

	if (recv_result != sf::Socket::NotReady)
	{
		if (received > 0)
			process_data(net_buf, received);
		else
			return;
	}

	for (int i = avatar.m_x - CLIENT_WIDTH / 2; i < avatar.m_x + CLIENT_WIDTH / 2; ++i)
		for (int j = avatar.m_y - CLIENT_HEIGHT / 2; j < avatar.m_y + CLIENT_HEIGHT / 2; ++j)
		{
			int tile_x = i - g_left_x;
			int tile_y = j - g_top_y;
			if ((i < 0) || (j < 0)) continue;
			if ((i > WORLD_WIDTH - 1) || (j > WORLD_HEIGHT - 1))continue;
			if (g_map[i][j] == 0) {
				tile1.a_move(TILE_WIDTH * tile_x + 7, TILE_WIDTH * tile_y + 7);
				tile1.a_draw();
			}
			else if(g_map[i][j] == 1)
			{
				tile2.a_move(TILE_WIDTH * tile_x + 7, TILE_WIDTH * tile_y + 7);
				tile2.a_draw();
			}
			else
			{
				tile3.a_move(TILE_WIDTH * tile_x + 7, TILE_WIDTH * tile_y + 7);
				tile3.a_draw();
			}
			if (!(i % 8) & !(j % 8)) {
				ghost.a_move(TILE_WIDTH * tile_x + 7, TILE_WIDTH * tile_y + 7);
				ghost.a_draw();
			}
		}
	avatar.draw();
	for (auto& npc : npcs) 
		npc.second.draw();
	sf::Text text;
	text.setFont(g_font);
	char buf[100];
	sprintf_s(buf, "(%d, %d)", avatar.m_x, avatar.m_y);
	text.setString(buf);
	g_window->draw(text);

	sprintf_s(buf, "Level-%hd, Hp-%hd, Exp-%d", avatar.level, avatar.hp, avatar.exp);
	text.setString(buf);
	text.setCharacterSize(20);
	text.setPosition(CLIENT_WIDTH * TILE_WIDTH / 4, 0.f);
	g_window->draw(text);

	for (int i = 0; i < g_chatLog.size(); ++i) {
		g_chatLog[i].setPosition(0,
			CLIENT_HEIGHT * TILE_WIDTH * 0.75 + 20 * i);
		g_window->draw(g_chatLog[i]);
	}
}

void send_packet(void* packet)
{
	char* p = reinterpret_cast<char*>(packet);
	size_t sent;
	sf::Socket::Status st = g_socket.send(p, p[0], sent);
}

void send_move_packet(unsigned char dir)
{
	MoveRequest m_packet;
	m_packet.type = CS_MOVE;
	m_packet.size = sizeof(m_packet);
	m_packet.direction = dir;
	m_packet.move_time = duration_cast<seconds>(high_resolution_clock::now()
		.time_since_epoch()).count();
	send_packet(&m_packet);
}

void send_logout_packet()
{
	LogoutRequest p;
	p.type = CS_LOGOUT;
	p.size = sizeof(p);
	send_packet(&p);
}

void send_atk_packet()
{
	AttackRequest p;
	p.type = CS_ATTACK;
	p.size = sizeof(p);
	p.atkTime = duration_cast<seconds>(high_resolution_clock::now()
		.time_since_epoch()).count();
	send_packet(&p);
}

int main()
{
	wcout.imbue(locale("korean"));
	std::cout << "IP주소를 입력하세요:";
	string s;
	cin >> s;
	sf::Socket::Status status = g_socket.connect(s.c_str(), SERVER_PORT);
	g_socket.setBlocking(false);

	if (status != sf::Socket::Done) {
		wcout << L"서버와 연결할 수 없습니다.\n";
		while (true);
	}

	std::cout << "플레이어 아이디를 입력하세요:";
	cin >> s;

	client_initialize();

	LoginRequest l_packet;
	l_packet.size = sizeof(l_packet);
	l_packet.type = CS_LOGIN;
	sprintf_s(l_packet.name, s.c_str());
	strcpy_s(avatar.name, l_packet.name);
	avatar.set_name(l_packet.name);
	send_packet(&l_packet);

	sf::RenderWindow window(sf::VideoMode(TILE_WIDTH * CLIENT_WIDTH, TILE_WIDTH * CLIENT_HEIGHT), "2D CLIENT");
	g_window = &window;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed) {
				int p_type = -1; 
				switch (event.key.code) {
				case sf::Keyboard::Left:
					send_move_packet(MV_LEFT);
					break;
				case sf::Keyboard::Right:
					send_move_packet(MV_RIGHT);
					break;
				case sf::Keyboard::Up:
					send_move_packet(MV_UP);
					break;
				case sf::Keyboard::Down:
					send_move_packet(MV_DOWN);
					break;
				case sf::Keyboard::Escape:
					send_logout_packet();
					window.close();
					break;
				case sf::Keyboard::A:
					send_atk_packet();
					break;
				}
			}
		}

		window.clear();
		client_main();
		window.display();
	}
	send_logout_packet();
	client_finish();

	return 0;
}