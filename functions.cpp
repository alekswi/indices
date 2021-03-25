#include "header.h"

void addRecord(Record*& head, string data, int verse) {
	stringstream stream;
	stream << data;
	string name, entry;
	stream >> name;
	getline(stream, entry);
	entry.erase(0, 1);
	Record* newRecord = new Record;
	newRecord->index_name = name;
	if (head == nullptr)
	{
		head = newRecord;
		addIndex(head->index, entry, verse);
	}
	else
	{
		Record* current = search(head, name);
		if (current == nullptr)
		{
			current = head;
			while (current->next != nullptr)
				current = current->next;
			current->next = newRecord;
			current = current->next;
		}
		else
			delete newRecord;
		addIndex(current->index, entry, verse);
	}
}

void addIndex(Index*& head, string entry, int verse) {
	Index* newIndex = new Index;
	newIndex->index_entry = entry;
	newIndex->index_verse = verse;
	if (head == nullptr)
		head = newIndex;
	else
	{
		if (head->next == nullptr)

			head->next = newIndex;
		else
		{
			Index* current = head;
			while (current->next != nullptr)
			{
				current = current->next;
			}
			current->next = newIndex;
		}
	}
}

Record* search(Record*& head, string name)
{
	Record* current = head;
	while (current->next != nullptr)
	{
		if (current->index_name == name)
			return current;
		current = current->next;
	}
	if (current->index_name == name)
		return current;
	else
	{
		return nullptr;
	}
}

string cut(string x) {
	int pos = x.find("}");
	x.erase(pos, 2);
	x.insert(pos, " ");
	return x;
}

void print_to_file(string everything, string output_file) {
	ofstream OFile;
	OFile.open(output_file);
	if (OFile) {
		OFile << everything;
	}
	OFile.close();
}

string entries(Index*& head)
{
	string everything;
	Index* current = head;
	do
	{
		everything += "\n" + current->index_entry + " " + to_string(current->index_verse);
		current = current->next;
	} while (current != nullptr);
	return everything;
}

string table(Record*& head, string data) {
	stringstream stream;
	stream << data;
	string name, header, everything = "\n";
	stream >> name;
	getline(stream, header);
	header.erase(0, 1);
	everything += header + "\n";
	for (int i = 0; i < header.length(); i++)
		everything += "=";
	everything += "\n";
	if (head != nullptr)
	{
		Record* current = search(head, name);
		if (current != nullptr)
			everything += entries(current->index);
		else
			everything += "\nNot found";
	}
	else
		everything += "\nNot found";
	return everything;
}
void clear_record(Index*& head) {
	while (head->next != nullptr) {
		Index* current = head;
		head = head->next;
		delete current;
	}
	delete head;
}

void clean_memory(Record*& head) {
	if (head != nullptr) {
		while (head->next != nullptr) {
			Record* current = head;
			head = head->next;
			clear_record(current->index);
			delete current;
		}
		clear_record(head->index);
		delete head;
	}
}

void read_file(string input_file, string output_file) {
	ifstream IFile;
	IFile.open(input_file);
	if (IFile) {
		Record* head = nullptr;
		string everything, line;
		int verse = 1;
		while (getline(IFile, line))
		{
			int first = 0;
			while (line.find("\\index{", first) != string::npos)
			{
				int first = line.find("\\index{") + 1;
				string to_index;
				int size = line.find("}", line.find("}") + 1) - first;
				to_index = cut(line.substr(first + 6, size - 6));
				addRecord(head, to_index, verse);
				line.erase(first - 1, size + 2);
				if (line.find(" ") == 0)
					line.erase(0, 1);
			}
			if (line.find("\\printindex{") != string::npos)
			{
				int first = line.find("\\printindex{");
				string to_index;
				int size = line.find("}", line.find("}") + 1) - first + 1;
				to_index = cut(line.substr(first + 12, size - 13));
				line = table(head, to_index);
			}
			everything += line + '\n';
			verse++;
		}
		print_to_file(everything, output_file);
		clean_memory(head);
	}
	else
		cout << "Plik o nazwie " << input_file << " nie istnieje!" << endl;
	IFile.close();
};