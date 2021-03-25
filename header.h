#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
//#include "debug.h"

using namespace std;

/** Lista do przechowywania nazwy wejscia */
struct Index
{
	string index_entry; ///< nazwa wejscia
	int index_verse; ///< wers wejscia
	Index* next = nullptr;
};

/** Glowna lista do przechowywania nazwy i poczatku indexu */
struct Record
{
	string index_name; ///< nazwa indexu
	Index* index = nullptr; ///< wskaznik na index
	Record* next = nullptr;
};

/**
 * Dodanie nowego rekordu
 * @param head wskaznik na poczatek glownej listy
 * @param data string zawierajacy nazwe i wejscie indexu
 * @param verse numer wersu, w ktorym znajdowal sie index
 */
void addRecord(Record*& head, string data, int verse);

/**
 * Dodawanie na koncu listy nowego indexu
 * @param head wskaznik na poczatek listy
 * @param data string zawierajacy wejscie indexu
 * @param verse numer wersu, w ktorym znajdowal sie index
 */
void addIndex(Index*& head, string entry, int verse);

/**
 * Przeszukiwanie czy istnieje record i zwrocenie pozycji
 * @param head wskaznik na poczatek glownej listy
 * @param name string zawierajacy nazwe indexu
 * @result wskaznik na znaleziony record z podana nazwa indexu
 */
Record* search(Record*& head, string name);

/**
 * Wycinanie z stringa nazwy i wejscia indexu
 * @param x string do wyciecia
 * @result wyciety string
 */
string cut(string x);

/**
 * Wypisywanie informacji do pliku
 * @param everything string do wypisania do pliku
 * @param output_file nazwa pliku do zapisu
 */
void print_to_file(string everything, string output_file);

/**
 * Zwrocenie wejscia indexu
 * @param head wskaznik na poczatek listy
 * @result wszystkie wystapienia danego indexu
 */
string entries(Index*& head);

/**
 * Zwrocenie wszystkich wejsc w indexie i nazwy indeksu
 * @param head wskaznik na poczatek glownej listy
 * @param data string zawierajacy nazwe indexu i artykulu
 * @result string zawierajacy nazwe indexu i jego wszystkie wejscia
 */
string table(Record*& head, string data);

/**
 * Czyszczenie recordu
 * @param head wskaznik na poczatek listy indeksow
 */
void clear_record(Index*& head);

/**
 * Czyszczenie pamieci
 * @param head wskaznik na poczatek glownej listy
 */
void clean_memory(Record*& head);

/**
 * Czytanie pliku
 * @param input_file nazwa pliku do czytania
 * @param output_file nazwia pliku do zapisania
 */
void read_file(string input_file, string output_file);