#include <iostream>
#include <fstream>

using namespace std;

struct pokemon{
    int id;
    string nome;
    string tipo;
    string tipo2;
    int total;
    int hp;
    int ataque;
    int defesa;
    int spataque;
    int spdefesa;
    int speed;
    int geracao;
    bool lendario;
};

string pokemonToString(pokemon &pokemon){
    return "ID: " + to_string(pokemon.id) +
           ", Nome: " + pokemon.nome +
           ", Tipo: " + pokemon.tipo +
           (pokemon.tipo2.empty() ? "" : ", Tipo2: " + pokemon.tipo2) +
           ", Total: " + to_string(pokemon.total) +
           ", HP: " + to_string(pokemon.hp) +
           ", Ataque: " + to_string(pokemon.ataque) +
           ", Defesa: " + to_string(pokemon.defesa) +
           ", SpAtaque: " + to_string(pokemon.spataque) +
           ", SpDefesa: " + to_string(pokemon.spdefesa) +
           ", Velocidade: " + to_string(pokemon.speed) +
           ", Geração: " + to_string(pokemon.geracao) +
           ", Lendário: " + (pokemon.lendario ? "Sim" : "Não");
}

void le_arquivo(pokemon *pokedex, int &tamPokedex, ifstream &entrada){
    for (int i = 0; i < tamPokedex; i++)
    {
        entrada >> pokedex[i].id;
        entrada.ignore();
        getline(entrada, pokedex[i].nome, ',');
        getline(entrada, pokedex[i].tipo, ',');
        getline(entrada, pokedex[i].tipo2, ',');
        entrada >> pokedex[i].total;
        entrada.ignore();
        entrada >> pokedex[i].hp;
        entrada.ignore();
        entrada >> pokedex[i].ataque;
        entrada.ignore();
        entrada >> pokedex[i].defesa;
        entrada.ignore();
        entrada >> pokedex[i].spataque;
        entrada.ignore();
        entrada >> pokedex[i].spdefesa;
        entrada.ignore();
        entrada >> pokedex[i].speed;
        entrada.ignore();
        entrada >> pokedex[i].geracao;
        entrada.ignore();
        entrada >> pokedex[i].lendario;
    }

    entrada.close();
}

void adiciona(pokemon *&pokedex, int &tamPokedex, int &tamMax, int margem){
    if (tamPokedex >= tamMax)
    {
        tamMax += margem;
        pokemon *novoPokedex = new pokemon[tamMax];

        for (int i = 0; i < tamPokedex; i++)
        {
            novoPokedex[i] = pokedex[i];
        }

        delete[] pokedex;
        pokedex = novoPokedex;
    }

    pokemon novoPokemon;

    cout << "Digite os dados do novo Pokémon:" << endl;

    cout << "ID: ";
    cin >> novoPokemon.id;
    cin.ignore();

    cout << "Nome: ";
    getline(cin, novoPokemon.nome);

    cout << "Tipo 1: ";
    getline(cin, novoPokemon.tipo);

    cout << "Tipo 2 (deixe em branco se não houver): ";
    getline(cin, novoPokemon.tipo2);

    cout << "HP: ";
    cin >> novoPokemon.hp;

    cout << "Ataque: ";
    cin >> novoPokemon.ataque;

    cout << "Defesa: ";
    cin >> novoPokemon.defesa;

    cout << "SpAtaque: ";
    cin >> novoPokemon.spataque;

    cout << "SpDefesa: ";
    cin >> novoPokemon.spdefesa;

    cout << "Speed: ";
    cin >> novoPokemon.speed;

    novoPokemon.total = novoPokemon.hp + novoPokemon.ataque + novoPokemon.defesa + novoPokemon.spataque + novoPokemon.spdefesa + novoPokemon.speed;

    cout << "Geração: ";
    cin >> novoPokemon.geracao;

    cout << "Lendário (1 para sim, 0 para não): ";
    cin >> novoPokemon.lendario;

    pokedex[tamPokedex] = novoPokemon;
    tamPokedex++;
}

void exclui(pokemon *&pokedex, int &tamPokedex, int &tamMax, int margem){
    int idExcluir;
    cout << "Digite o ID do Pokémon a ser excluído: ";
    cin >> idExcluir;

    int indice = -1;
    for (int i = 0; i < tamPokedex; i++){
        if (pokedex[i].id == idExcluir){
            indice = i;
        }
    }

    cout << indice;

    if (indice == -1){
        cout << "Pokémon com ID " << idExcluir << " não encontrado." << endl;
        return;
    }

    for (int i = indice; i < tamPokedex - 1; i++){
        pokedex[i] = pokedex[i + 1];
    }

    tamPokedex--;
    cout << "Pokémon com ID " << idExcluir << " foi excluído." << endl;

    /*if (tamPokedex < tamMax - margem)
    {
        tamMax -= margem;
        pokemon *novoPokedex = new pokemon[tamMax];

        for (int i = 0; i < tamPokedex; i++)
        {
            novoPokedex[i] = pokedex[i];
        }

        delete[] pokedex;
        pokedex = novoPokedex;
    }*/
}
void salva_arquivo(pokemon *pokedex, int tamPokedex, string cabecalho){
    ofstream saida("PokemonSaida.csv");

    saida << cabecalho << endl;
    saida << tamPokedex << endl;
    for (int i = 0; i < tamPokedex; i++)
    {
        saida << pokedex[i].id << ","
              << pokedex[i].nome << ","
              << pokedex[i].tipo << ","
              << (pokedex[i].tipo2.empty() ? "" : pokedex[i].tipo2) << ","
              << pokedex[i].total << ","
              << pokedex[i].hp << ","
              << pokedex[i].ataque << ","
              << pokedex[i].defesa << ","
              << pokedex[i].spataque << ","
              << pokedex[i].spdefesa << ","
              << pokedex[i].speed << ","
              << pokedex[i].geracao << ","
              << pokedex[i].lendario << endl;
    }
    saida.close();
}
bool compara(pokemon x, pokemon y, string campo, bool crescente){
    if (campo == "nome")
        return crescente ? x.nome < y.nome : x.nome > y.nome;
    else if (campo == "id")
        return crescente ? x.id < y.id : x.id > y.id;
    else if (campo == "total")
        return crescente ? x.total < y.total : x.total > y.total;
    else if (campo == "hp")
        return crescente ? x.hp < y.hp : x.hp > y.hp;
    else if (campo == "ataque")
        return crescente ? x.ataque < y.ataque : x.ataque > y.ataque;
    else if (campo == "defesa")
        return crescente ? x.defesa < y.defesa : x.defesa > y.defesa;
    else if (campo == "spataque")
        return crescente ? x.spataque < y.spataque : x.spataque > y.spataque;
    else if (campo == "spdefesa")
        return crescente ? x.spdefesa < y.spdefesa : x.spdefesa > y.spdefesa;
    else if (campo == "speed")
        return crescente ? x.speed < y.speed : x.speed > y.speed;

    return false;
}
void quicksort(pokemon *pokedex, int inicio, int fim, string campo, bool crescente){
    if (inicio > fim)
        return;

    int pivoIndex = inicio;
    pokemon pivo = pokedex[fim];

    pokemon aux;
    for (int i = inicio; i < fim; i++)
    {
        if (compara(pokedex[i], pivo, campo, crescente))
        {
            swap(pokedex[i], pokedex[pivoIndex]);
            pivoIndex++;
        }
    }

    swap(pokedex[pivoIndex], pokedex[fim]);

    quicksort(pokedex, inicio, pivoIndex - 1, campo, crescente);
    quicksort(pokedex, pivoIndex + 1, fim, campo, crescente);
}
pokemon *busca_binaria(pokemon *pokedex, int inicio, int fim, string valor, bool porNome){
    if (inicio > fim)
        return nullptr;

    int meio = (inicio + fim) / 2;

    if (porNome)
    {
        if (pokedex[meio].nome == valor)
            return &pokedex[meio];
        else if (pokedex[meio].nome < valor)
            return busca_binaria(pokedex, meio + 1, fim, valor, porNome);
        else
            return busca_binaria(pokedex, inicio, meio - 1, valor, porNome);
    }
    else
    {
        int id = stoi(valor);
        if (pokedex[meio].id == id)
            return &pokedex[meio];
        else if (pokedex[meio].id < id)
            return busca_binaria(pokedex, meio + 1, fim, valor, porNome);
        else
            return busca_binaria(pokedex, inicio, meio - 1, valor, porNome);
    }
}

void exibirAscii(){
    cout << R"(
                     ⢠⣤⣶⣿⣷⣤⣀⣀⣀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣤⠀⠀⠸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣤⣤⣤⣶⣶⣾⡿⠃⠀⠀⠀⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⢿⣶⣤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢶⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⢀⣠⣾⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠈⠛⠿⣿⣿⣿⣿⣿⣿⣧⠀⠈⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⣿⣷⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⣀⣤⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢿⣿⣿⣿⣿⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⣿⣿⣿⣿⣷⣦⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⣰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⡀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⣿⣿⣿⣿⣿⣿⣿⣷⣄⠀⠀⠀⠀⠀
⠀⠀⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⣄⡀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⡄⠀⠀⠀⠀⠀⠀⠀⠀⢠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣤⡀⠀⠀
⢀⣾⣿⣿⣿⣿⣿⣿⠿⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣤⣀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣧⠀⠀⠀⠀⠀⢀⣠⣤⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡄⠀
⣼⣿⣿⣿⠟⠋⠁⠀⠀⠀⠈⠹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣶⣠⣿⣿⣿⣿⣿⣿⣄⣤⣶⣶⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⠀
⣿⣿⡿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠈⢿⣿⣿⣿⠟⠛⠛⢛⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠛⠻⣿⣿⣿⣿⣿⣿⡆
⢻⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠿⠋⠀⠀⣀⣴⣾⡿⠿⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠋⠀⠀⢰⣿⣿⠻⣿⣿⣿⣧
⠈⠿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⣾⣿⣿⣇⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠈⢻⣿⣿⣿⣿⡿⠃⠀⠀⠀⢸⣿⣿⡆⠈⢿⣿⣿
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠿⢿⣿⡟⢿⣿⠀⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⢀⣾⡿⣿⣿⠿⣿⠀⠀⠀⠀⣸⣿⣿⣷⠀⠸⣿⡿
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠛⠀⠘⠉⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡀⠀⠀⠙⠁⠸⠟⠀⠀⠀⠀⠀⢸⣿⣿⣿⣧⣄⠀⣿⠃
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣀⣀⡀⠀⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⢻⣿⣿⣿⠿⠋⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⢀⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⠀⠀⠀⠀⠀⠀⠀⣠⣼⠟⠁⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣄⣀⣤⣴⣶⣿⠟⠁⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠛⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠈⠛⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠿⠿⠟⠛⠛⠉⠉⠉⠉⠉⠛⠛⠿⠿⠿⠿⣿⣿⣿⣿⣿⣿⡋⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠉⢹⣿⣿⣿⣿⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⠛⠿⢿⣿⣿⣿⠦⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⠛⢹⡟⠙⠻⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠀⠈⠀
 _____    ____   _  __ ______  _____   ______ __   __
 |  __ \  / __ \ | |/ /|  ____||  __ \ |  ____|\ \ / /
 | |__) || |  | || ' / | |__   | |  | || |__    \ V /
 |  ___/ | |  | ||  <  |  __|  | |  | ||  __|    > <
 | |     | |__| || . \ | |____ | |__| || |____  / . \
 |_|      \____/ |_|\_\|______||_____/ |______|/_/ \_\
)" << endl;
}

void exibir_menu(){
    cout << "================= MENU POKEDEX =================" << endl;
    cout << "1. Exibir Todos Pokemons" << endl;
    cout << "2. Adicionar Pokemon" << endl;
    cout << "3. Excluir Pokemon" << endl;
    cout << "4. Buscar Pokemon" << endl;
    cout << "5. Ordenar Pokemons" << endl;
    cout << "6. Salvar em arquivo CSV" << endl;
    cout << "7. Exibir de X a Y" << endl;
    cout << "8. Limpar Tela" << endl;
    cout << "0. Sair" << endl;
    cout << "================================================" << endl;
    cout << "Escolha uma opcao: ";
}

int main(){
    ifstream entrada("Pokemon.csv");
    string cabecalho;
    int tamPokedex;

    getline(entrada, cabecalho);
    entrada >> tamPokedex;

    int margem = 5;
    int tamMax = tamPokedex + margem;
    pokemon *pokedex = new pokemon[tamMax];

    le_arquivo(pokedex, tamPokedex, entrada);

    int opcao = 0;
    exibirAscii();
    do
    {
        exibir_menu();
        cin >> opcao;

        switch (opcao)
        {
        case 1:
        {
            for (int i = 0; i < tamPokedex; i++)
            {
                cout << pokemonToString(pokedex[i]) << endl;
            }
            break;
        }

        case 2:
        {
            adiciona(pokedex, tamPokedex, tamMax, margem);
            break;
        }

        case 3:
        {
            exclui(pokedex, tamPokedex, tamMax, margem);
            break;
        }
        case 4:
        {
            cout << "Deseja buscar por (0) Nome ou (1) Id? ";
            int opcaoBusca;
            cin >> opcaoBusca;

            if (opcaoBusca)
            {
                string id;
                cout << "Digite o ID do Pokemon: ";
                cin >> id;
                quicksort(pokedex, 0, tamPokedex - 1, "id", 1);
                pokemon *busca = busca_binaria(pokedex, 0, tamPokedex - 1, id, 0);
                busca == nullptr ? cout << "Pokemon nao encontrado." << endl : cout << pokemonToString(*busca) << endl;
            }
            else
            {
                string nome;
                cout << "Digite o Nome do Pokemon: ";
                cin >> nome;
                quicksort(pokedex, 0, tamPokedex - 1, "nome", 1);
                pokemon *busca = busca_binaria(pokedex, 0, tamPokedex - 1, nome, 1);
                busca == nullptr ? cout << "Pokemon nao encontrado." << endl : cout << pokemonToString(*busca) << endl;
            }
            break;
        }

        case 5:
        {
            string campo;
            bool crescente;
            cout << "Por qual campo deseja ordenar? (opções: nome, id, total, hp, ataque, defesa, spataque, spdefesa, speed): ";
            cin >> campo;

            cout << "Deseja ordenar de forma crescente? (1 para sim, 0 para não): ";
            cin >> crescente;

            quicksort(pokedex, 0, tamPokedex - 1, campo, crescente);

            cout << "Pokémons ordenados com sucesso!" << endl;
            break;
        }

        case 6:
        {
            salva_arquivo(pokedex, tamPokedex, cabecalho);
            break;
        }

        case 7:
            int comeco;
            int fim;

            cout << "Digite o elemento que voce deseja comecar: ";
            cin >> comeco;
            cout << "Agora digite o elemento que voce deseja terminar: ";
            cin >> fim;

            for (int i = comeco - 1; i < fim; i++)
            {
                cout << pokemonToString(pokedex[i]) << endl;
            }
            break;

        case 8:
            system("clear||cls");
            exibirAscii();
            break;
        case 0:
           cout << "Encerrando o programa. Até logo!" << endl;
           break;
        default:
            cout << "Opcao invalida! Tente novamente." << endl;
        }

    } while (opcao != 0);

    delete[] pokedex;
    return 0;
}
