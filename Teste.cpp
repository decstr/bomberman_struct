#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <vector>
#include <chrono>
#include <locale.h>

using namespace std;
using namespace std::chrono;

// Estrutura para o display in game
struct Display {
    float tempo;
    int movimento;
    int qtdBombas;
};

// Estrutura para representar os inimigos
struct Inimigo
{
    int x;
    int y;
};

// Estrutura para representar os jogadores
struct Jogador
{
    short int x;
    short int y;
    short int vidas = 1;
    short int maximoBombas = 1;
    bool resisteBomba = false;
    bool raioBomba = 1;
    bool bombaRelogio = false;
    bool noclip = false;
    bool noclipBomba = false;
};

// Estrutura para representar as bombas
struct Bomba
{
    bool ativa;
    short int x;
    short int y;
};


// Função para verificar se o movimento é válido

bool verificaMovimento(int m[][15], int x, int y)
{
    if (m[x][y] == 8){
        return m[x][y];
    }
    return m[x][y] == 0;
}

//bool chancePowerUp ()
//{
//    int chance = rand() % 100+1;
//    if (chance < 100)
//    {
//        return true;
//    }
//    else {
//
//        return false;
//    }
//
//}

//int powerUp()
//{
//    chancePowerUp();
//    if (chancePowerUp)
//     int tipoPowerUp = 2; //0 para aumento da quantidade de bombas, 1 vida extra, 2 para invencibilidade contra bomba e 3 para atravessar blocos quebraveis
//        return tipoPowerUp;
//
//}
//bool resisteBomba()
//{
//    int tipo = powerUp();
//    if (tipo == 2){
//        return resisteBomba;
//
//    }
//    else {
//        return false;
//    }
//}

// Função para mover os inimigos

void moverInimigos(int m[][15], vector<Inimigo>& inimigos)
{
    for (auto& inimigo : inimigos)
    {
        int dir = rand() % 4; // 0 para cima, 1 para baixo, 2 para esquerda, 3 para direita
        switch (dir)
        {
        case 0:
            if (verificaMovimento(m, inimigo.x - 1, inimigo.y))
            {
                inimigo.x--;
            }
            break;
        case 1:
            if (verificaMovimento(m, inimigo.x + 1, inimigo.y))
            {
                inimigo.x++;
            }
            break;
        case 2:
            if (verificaMovimento(m, inimigo.x, inimigo.y - 1))
            {
                inimigo.y--;
            }
            break;
        case 3:
            if (verificaMovimento(m, inimigo.x, inimigo.y + 1))
            {
                inimigo.y++;
            }
            break;
        }
    }

}

// FunÃ§Ã£o para definir o estado do jogo
void definirJogo(int m[][15], const vector<Inimigo>& inimigos, const Jogador& jogador, const Bomba& bomba, int& contadorPiscadasBomba, const Display& ingameDisplay)
{
    COORD coord;
    coord.X = 0;
    coord.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if (i == jogador.x && j == jogador.y)
            {
                cout << char(36);
            }
            else if (bomba.x == i && bomba.y == j && bomba.ativa && contadorPiscadasBomba % 2 == 0)
            {
                cout << char(184); // Exibe a bomba se o contador de piscadas for par
            }
            else
            {
                bool verificaInimigo = false;
                for (const auto& inimigo : inimigos)
                {
                    if (i == inimigo.x && j == inimigo.y)
                    {
                        cout << char(159);
                        verificaInimigo = true;
                        break;
                    }
                }
                if (!verificaInimigo)

                {
                    switch (m[i][j])
                    {
                    case 0:
                        cout << " ";
                        break;
                    case 1:
                        cout << char(219);
                        break;
                    case 2:
                        cout << char(35);
                        break; // Paredes quebrÃ¡veis
                    case 3:
                        cout << char(157);
                        break; // bomba
                    case 4:
                        cout << char(159);
                        break; // Inimigo
                    case 5:
                        cout << char(36);
                        break; // Jogador
                    case 7:
                        cout << char(134);

                        break; // explosão
                    case 8:
                        cout << char(5);
                        break; //powerup
                    case 9:
                        cout << char(75);
                        break;
                    case 10:
                        cout << char(75);
                        break;
                    case 11:
                        cout << char(75);
                        break;
                    case 12:
                        cout << char(75);
                        break;
                    case 13:
                        cout << char(75);
                        break;
                     case 14:
                        cout << char(75);
                        break;

                    }
                }
            }
        }
        cout << "\n";
    }
    cout << "Quantidade de movimentos: " << ingameDisplay.movimento << endl;
    cout << "Quantidade de bombas usadas: " << ingameDisplay.qtdBombas << endl;
    cout << "Tempo: " << ingameDisplay.tempo << " segundos" << endl;
}

void resetMapa(int m[][15], vector<Inimigo>& inimigos,  Jogador& jogador, Bomba& bomba, int& contadorPiscadasBomba, Display& ingameDisplay)
{
    // Reinicializa o mapa com suas configuraÃ§Ãµes iniciais
    Sleep(1000);
    system("cls");
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if (i == jogador.x && j == jogador.y)
            {
                cout << char(36);
            }
            else if (bomba.x == i && bomba.y == j && bomba.ativa && contadorPiscadasBomba % 2 == 0)
            {
                cout << char(184); // Exibe a bomba se o contador de piscadas for par
            }
            else
            {
                bool verificaInimigo = false;
                for (const auto& inimigo : inimigos)
                {
                    if (i == inimigo.x && j == inimigo.y)
                    {
                        cout << char(159);
                        verificaInimigo = true;
                        break;
                    }
                }
                if (!verificaInimigo)
                {
                    switch (m[i][j])
                    {
                    case 0:
                        cout << " ";
                        break;
                    case 1:
                        cout << char(219);
                        break;
                    case 2:
                        cout << char(35);
                        break; // Paredes quebrÃ¡veis
                    case 3:
                        cout << char(157);
                        break; // bomba
                    case 4:
                        cout << char(159);
                        break; // Inimigo
                    case 5:
                        cout << char(36);
                        break; // Jogador
                    case 7:
                        cout << char(134);
                        break; // explosÃ£o
                    case 8:
                        cout << char(75);
                        break;
                    case 9:
                        cout << char(75);
                        break;
                    case 10:
                        cout << char(75);
                        break;
                    case 11:
                        cout << char(75);
                        break;
                    case 12:
                        cout << char(75);
                        break;
                    case 13:
                        cout << char(75);
                        break;
                    case 14:
                        cout << char(75);
                        break;

                    }
                }
            }
        }
        cout << "\n";
    }

    // Reposiciona os inimigos
    inimigos.clear(); // Limpa o vetor de inimigos
    for (int k = 0; k < 3; k++)   //Da respawn nos inimigos
    {
        Inimigo novoInimigo;
        do
        {
            novoInimigo.x = rand() % 15;
            novoInimigo.y = rand() % 15;
        }
        while (m[novoInimigo.x][novoInimigo.y] != 0);   // Garante que o inimigo nÃ£o nasÃ§a em uma parede
        inimigos.push_back(novoInimigo); // Adiciona o novo inimigo ao vetor
    }

    // Limpa a Ã¡rea de explosÃ£o
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if (m[i][j] == 7)
            {
                m[i][j] = 0;
            }
        }
    }

        // Recoloca as paredes quebraveis
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if (m[i][j] == 2)
            {
                m[i][j] = 0;
            }
        }
    }

    // Define um minimo e um maximo de paredes quebraveis no mapa
    int minParedesQuebraveis = 10;
    int maxParedesQuebraveis = 20;

    // Gera uma quantidade aleatÃ³ria de paredes quebraveis limitadas no minimo e maximo
    int numParedesQuebraveis = rand() % (maxParedesQuebraveis - minParedesQuebraveis + 1) + minParedesQuebraveis;

    // Coloca as paredes quebraveis de modo aleatÃ³rio
    for (int k = 0; k < numParedesQuebraveis; k++)
    {
        int x, y;
        do
        {
            x = rand() % 15;
            y = rand() % 15;
        }
        while (m[x][y] != 0);   // Garante que a posiÃ§Ã£o esteja vazia (nÃ£o Ã© parede existente, inimigo ou o jogador)
        m[x][y] = 2;
    }

    // Reinicializa as variÃ¡veis relacionadas ao jogo
    jogador.x = 1;
    jogador.y = 1;
    bomba.ativa = false;
    bomba.x = 0;
    bomba.y = 0;
    contadorPiscadasBomba = 0;
    ingameDisplay.movimento = 0;
    ingameDisplay.qtdBombas = 0;
    ingameDisplay.tempo = 0;
}

// Função para destruir uma parede quebrável e possivelmente gerar um power-up
void destruirParedeQuebravel(int m[][15],Bomba& bomba, Jogador& jogador, Display& ingameDisplay)
{
    int i, j;
    int minPower = 8;
    int maxPower = 14;
    int amplitude = (maxPower - minPower) + 1;
    int tipoPowerUp = rand()% amplitude + minPower;
    int powerUp;
    powerUp = 1;

                    // Define o símbolo correspondente ao tipo de power-up gerado
                    switch (tipoPowerUp)
                    {
                    case 0:
                        m[i][j] = 9; // Símbolo para aumento da quantidade de bombas
                        break;
                    case 1:
                        m[i][j] = 8; // Símbolo para vida extra
                        break;
                    case 2:
                        m[i][j] = 10; // Símbolo para invencibilidade contra bomba
                        break;
                    case 3:
                        m[i][j] = 11; // Símbolo para bomba relógio
                        break;
                    case 4:
                        m[i][j] = 12; // Símbolo para noclip
                        break;
                    case 5:
                        m[i][j] = 13; // Símbolo para noclip da bomba
                        break;
                    case 6:
                        m[i][j] = 14; // Símbolo para aumento do raio da bomba
                        break;
                    // Adicione outros casos conforme necessário
                    default:
                        m[i][j] = 20; // Símbolo padrão para power-ups desconhecidos
                        break;
                    }
    if(powerUp == 1 && m[bomba.x + i][bomba.y] == 2){
        m[bomba.x + i][bomba.y] = tipoPowerUp;
    }else if(powerUp == 1 && m[bomba.x][bomba.y + i] == 2){
        m[bomba.x][bomba.y + i] = tipoPowerUp;

    }else if(powerUp == 1 && m[bomba.x - i][bomba.y] == 2){
        m[bomba.x - i][bomba.y] = tipoPowerUp;

    }else if(powerUp == 1 && m[bomba.x][bomba.y - i] == 2){
        m[bomba.x][bomba.y - i] = tipoPowerUp;
    }



}



// FunÃ§Ã£o para verificar se o jogo acabou
bool verificaGameOver(int jogadorX, int jogadorY, const vector<Inimigo>& inimigos)
{
    for (const auto& inimigo : inimigos)
    {
        if (jogadorX == inimigo.x && jogadorY == inimigo.y)
        {
            return true; // Jogador atingido pelo inimigo
        }
    }
    return false; // Jogador nÃ£o atingido
}

int main()
{
    //setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));

    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(out, &cursorInfo);

    char tecla;

    int m[15][15]=
    {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 1,
        1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
        1, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 1,
        1, 0, 1, 0, 1, 0, 1, 0, 1, 2, 1, 0, 1, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
        1, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 1,
        1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
        1, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 2, 0, 0, 1,
        1, 2, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 2, 1,
        1, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 0, 1,
        1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
        1, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    };

    vector<Inimigo> inimigos(3); // Vetor para armazenar os inimigos
    for (auto& inimigo : inimigos)
    {
        do
        {
            inimigo.x = rand() % 15;
            inimigo.y = rand() % 15;
        }
        while (m[inimigo.x][inimigo.y] != 0);   // Garante que o inimigo nÃ£o nasÃ§a em uma parede
    }
    Jogador jogador = {1, 1};
    Bomba bomba = {0, 0, false};
    Display ingameDisplay = {0, 0, 0};

    auto ultimoTempoPlayer = steady_clock::now();
    auto ultimoTempoInimigo = steady_clock::now();
    auto ultimoTempoBomba = steady_clock::now();
    auto ultimoTempoBomba2 = steady_clock::now();
    auto inicioContadorInGame = steady_clock::now();
    milliseconds updateTempoPlayer(50); // Controle da velocidade de movimento do jogador
    milliseconds updateTempoInimigo(250); // Controla a velocidade de movimento do inimigo
    milliseconds tempoExplosao(3000); // Tempo de explosÃ£o da bomba (3 segundos)
    milliseconds tempoPiscadaBomba(500); // Intervalo de tempo para a piscada da bomba
    milliseconds timerDisplayExplosao(50); // Timer referente ao tempo no qual os caracteres da explosÃ£o permanecem no mapa
    milliseconds marcadorTempoInGame(1000); // Referente ao tempo mostrado in game
    int contadorPiscadasBomba = 0;


    int opcao; // VariÃ¡vel para armazenar a opÃ§Ã£o do menu

    do
    {
        cout << "=== MENU ===\n";
        cout << "1. Jogar\n";
        cout << "2. Sair\n";
        cout << "3. InformaÃ§Ãµes de desenvolvimento\n";
        cout << "Escolha uma opÃ§Ã£o: ";
        cin >> opcao;
        system("cls");

        switch (opcao)
        {
        case 1: // Jogar
            while (true)
            {
                auto tempoAtual = steady_clock::now();
                auto tempoAtual2 = steady_clock::now();
                auto tempoAtualContadorInGame = steady_clock::now();
                //powerUp();


                // MovimentaÃ§Ã£o do jogador
                auto contadorTempoPlayer = duration_cast<milliseconds>(tempoAtual - ultimoTempoPlayer);
                if (contadorTempoPlayer >= updateTempoPlayer)
                {
                    ultimoTempoPlayer = tempoAtual;

                    if (_kbhit())
                    {
                        tecla = getch();
                        switch (tecla)
                        {
                        case 72:
                        case 'w':
                            if (jogador.x > 0 && verificaMovimento(m, jogador.x - 1, jogador.y))
                            {
                                jogador.x--;
                                ingameDisplay.movimento++;
                            }
                            break;
                        case 80:
                        case 's':
                            if (jogador.x < 14 && verificaMovimento(m, jogador.x + 1, jogador.y))
                            {
                                jogador.x++;
                                ingameDisplay.movimento++;
                            }
                            break;
                        case 75:
                        case 'a':
                            if (jogador.y > 0 && verificaMovimento(m, jogador.x, jogador.y - 1))
                            {
                                jogador.y--;
                                ingameDisplay.movimento++;
                            }
                            break;
                        case 77:
                        case 'd':
                            if (jogador.y < 14 && verificaMovimento(m, jogador.x, jogador.y + 1))
                            {
                                jogador.y++;
                                ingameDisplay.movimento++;
                            }
                            break;
                        case 32: // Coloca a bomba
                            if (!bomba.ativa)
                            {
                                bomba.ativa = true;
                                bomba.x = jogador.x;
                                bomba.y = jogador.y;
                                ultimoTempoBomba2 = tempoAtual2;
                                ingameDisplay.qtdBombas++;
                                m[bomba.x][bomba.y] = 3; // Marca a posiÃ§Ã£o da bomba no mapa
                            }
                            break;
                        }
                        if (verificaGameOver(jogador.x, jogador.y, inimigos))
                        {
                            cout << "VocÃª perdeu! O inimigo te atingiu.\n";
                            resetMapa(m, inimigos, jogador, bomba, contadorPiscadasBomba,ingameDisplay); // Reseta o mapa
                            break;
                        }
                    }
                }

                // MovimentaÃ§Ã£o dos inimigos
                auto contadorTempoInimigo = duration_cast<milliseconds>(tempoAtual - ultimoTempoInimigo);
                if (contadorTempoInimigo >= updateTempoInimigo)
                {
                    ultimoTempoInimigo = tempoAtual;
                    moverInimigos(m, inimigos);
                    if (verificaGameOver(jogador.x, jogador.y, inimigos))
                    {
                        cout << "VocÃª perdeu! O inimigo te atingiu.\n";
                        resetMapa(m, inimigos, jogador, bomba, contadorPiscadasBomba,ingameDisplay); // Reseta o mapa
                        break;
                    }
                }

                //Timer in Game
                auto contadorTempoInGame = duration_cast<milliseconds>(tempoAtualContadorInGame - inicioContadorInGame);
                if (contadorTempoInGame >= marcadorTempoInGame){
                    ingameDisplay.tempo++;
                    inicioContadorInGame = tempoAtualContadorInGame;
                }

                // ExplosÃ£o da bomba
                auto contadorTempoBomba = duration_cast<milliseconds>(tempoAtual2 - ultimoTempoBomba2);
                if (bomba.ativa && contadorTempoBomba >= tempoExplosao)
                {
                    // Marca a explosÃ£o no mapa
                    m[bomba.x][bomba.y] = 0;
                    ultimoTempoBomba2 = tempoAtual;


                    // Verifica se a parede quebravel está na área de explosão

                    for (int i = -1; i <= 1; ++i)
                    {
                        for (int j = -1; j <= 1; ++j)
                        {
                            if (m[bomba.x + i][bomba.y] == 2 || m[bomba.x + i][bomba.y] == 0)   // Se for uma parede quebrÃ¡vel
                            {
                                m[bomba.x + i][bomba.y] = 7; // Explosão e Remove a parede quebrável do mapa
                                destruirParedeQuebravel(m, bomba, jogador, ingameDisplay);

                            }
                            else if(m[bomba.x][bomba.y + i] == 2 || m[bomba.x][bomba.y + i] == 0)
                            {
                                m[bomba.x][bomba.y + i] = 7; // Explosão e Remove a parede quebrável do mapa
                                destruirParedeQuebravel(m, bomba, jogador, ingameDisplay);


                            }
                            else if(m[bomba.x - i][bomba.y] == 2 || m[bomba.x - i][bomba.y] == 0)
                            {
                                m[bomba.x - i][bomba.y] = 7; // Explosão e Remove a parede quebrável do mapa
                                destruirParedeQuebravel(m, bomba, jogador, ingameDisplay);
                            }
                            else if(m[bomba.x][bomba.y - i] == 2 || m[bomba.x][bomba.y - i] == 0)
                            {
                                m[bomba.x][bomba.y - i] = 7; // Explosão e Remove a parede quebrável do mapa
                                destruirParedeQuebravel(m, bomba, jogador, ingameDisplay);

                            }
                        }
                    }

                    // Verifica se o jogador estÃ¡ na Ã¡rea de explosÃ£o, do/while verifica se o jogador tem o powerUp de resistencia a bomba
                    //resisteBomba();
                    //while (!jogador.resisteBomba)
                    //{

                        if (jogador.x == bomba.x || jogador.y == bomba.y)
                        {
                            if ((abs(jogador.x - bomba.x) <= 1 && jogador.y == bomba.y) ||
                                    (abs(jogador.y - bomba.y) <= 1 && jogador.x == bomba.x))
                            {
                                cout << "VocÃª perdeu! VocÃª foi atingido pela explosÃ£o.\n";
                                resetMapa(m, inimigos, jogador, bomba, contadorPiscadasBomba,ingameDisplay); // Reseta o mapa
                                break;
                            }
                        }

                    //}




                    // Verifica se o inimigo estÃ¡ na Ã¡rea de explosÃ£o
                    for (auto it = inimigos.begin(); it != inimigos.end();)
                    {
                        if ((abs(it->x - bomba.x) == 1 && it->y == bomba.y) || //verifica se o inimigo estÃ¡ a 1 posiÃ§Ã£o da bomba
                                (abs(it->y - bomba.y) == 1 && it->x == bomba.x))
                        {
                            it = inimigos.erase(it); // Remove o inimigo do vetor
                        }
                        else
                        {
                            ++it;
                        }
                    }
                    //Verifca se todos inimigos foram removidos do vetor
                    if (inimigos.empty())
                    {
                        // Todos os inimigos foram eliminados, o jogador ganha
                        cout << "ParabÃ©ns! Todos inimigos foram derrotados. VocÃª venceu! \n";
                        resetMapa(m, inimigos, jogador, bomba, contadorPiscadasBomba, ingameDisplay); // Reseta o mapa
                        break;
                    }



                    bomba.ativa = false;
                }
                // Timer que remove a explosÃ£o do mapa
                auto contadorDisplayExplosao = duration_cast<milliseconds>(tempoAtual - ultimoTempoBomba2);
                if (contadorDisplayExplosao >= timerDisplayExplosao && !bomba.ativa)
                {
                    for (int i = -1; i <= 1; ++i)
                    {
                        for (int j = -1; j <= 1; ++j)
                        {
                            if (m[bomba.x + i][bomba.y + j] == 7)
                            {
                                m[bomba.x + i][bomba.y + j] = 0;
                            }
                        }
                    }
                }

                // Atualiza a tela do jogo
                definirJogo(m, inimigos, jogador, bomba, contadorPiscadasBomba, ingameDisplay);

                // Controle da piscada da bomba
                auto contadorTempoPiscadaBomba = duration_cast<milliseconds>(tempoAtual - ultimoTempoBomba);
                if (bomba.ativa && contadorTempoPiscadaBomba >= tempoPiscadaBomba)
                {
                    ultimoTempoBomba = tempoAtual;
                    contadorPiscadasBomba++;
                }


            }
            break;
        case 2: // Sair
            cout << "Saindo do jogo...\n";
            break;
        case 3: // InformaÃ§Ãµes de desenvolvimento
            cout << "Desenvolvido por Matheus de Castro, JoÃ£o Marcos, Nicolas e Miguel Soares" << endl;
            cout << "MatÃ©ria: Algoritmos II" << endl;
            cout << "Professor Alex Rese" << endl;
            break;
        default:
            cout << "OpÃ§Ã£o invÃ¡lida. Por favor, escolha uma opÃ§Ã£o vÃ¡lida.\n";
        }
    }
    while (opcao != 2);

    return 0;
}
