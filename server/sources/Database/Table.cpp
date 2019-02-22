
// ██████╗  █████╗ ██████╗     ███████╗██╗          ██████╗ ██╗   ██╗███████╗██████╗
// ██╔══██╗██╔══██╗██╔══██╗    ██╔════╝██║         ██╔═══██╗██║   ██║██╔════╝██╔══██╗
// ██████╔╝███████║██████╔╝    █████╗  ██║         ██║   ██║██║   ██║█████╗  ██║  ██║
// ██╔══██╗██╔══██║██╔══██╗    ██╔══╝  ██║         ██║   ██║██║   ██║██╔══╝  ██║  ██║
// ██████╔╝██║  ██║██████╔╝    ███████╗███████╗    ╚██████╔╝╚██████╔╝███████╗██████╔╝
// ╚═════╝ ╚═╝  ╚═╝╚═════╝     ╚══════╝╚══════╝     ╚═════╝  ╚═════╝ ╚══════╝╚═════╝ 
// Table.cpp created 28/09/2017

#include <Logger.hpp>
#include "Table.hpp"

Database::Table::Table(const std::string &tableName, const std::string &dbName) :
    _tableName(tableName),
    _dbName(dbName)
{
    this->_lastId = 0;
}

Database::Table::~Table()
{

}

Database::ITable &Database::Table::addField(const Field &field)
{
    this->_rows[field] = {};
    return *this;
}

Database::ITable &Database::Table::addRow(const std::map<Field, Data> &row)
{
    for (auto &it : this->_rows)
        this->_rows[it.first][this->_lastId] = "";

    for (const auto &toAdd : row)
    {
        if (this->_rows.count(toAdd.first) == 1)
            this->_rows[toAdd.first][this->_lastId] = toAdd.second;
        else
            throw std::runtime_error("Cannot find: " + toAdd.first);
    }

    this->_lastId++;
    return *this;
}

Database::ITable &Database::Table::clear()
{
    this->_rows.clear();

    return *this;
}

Database::ITable &Database::Table::delRow(Database::Id ID)
{
    for (auto &it : this->_rows)
    {
        for (auto &i : it.second)
        {
            if (i.first == ID)
                it.second.erase(ID);
        }
    }
    return *this;
}

const std::vector<Database::Field> Database::Table::getColumnsName() const
{
    std::vector<Database::Field > Columns;

    for (const auto &_row : this->_rows)
        Columns.push_back(_row.first);

    return Columns;
}

void Database::Table::print()
{
    for (const auto &it : this->_rows)
    {
        for (const auto &i : it.second)
        {
            std::cout << "Field: " << it.first << std::endl;
            std::cout << "Id: " << i.first << std::endl;
            std::cout << "Data: " << i.second << std::endl;
        }
    }
}

Database::ITable &Database::Table::removeField(const Database::Field &field)
{
    this->_rows.erase(field);
    return *this;
}

Database::ITable &Database::Table::save()
{
    std::remove(std::string(this->_dbName + "/" + this->_tableName + ".db").c_str());
    std::ofstream file;

    file.open(this->_dbName + "/" + this->_tableName + ".db", std::ios::out);

    _saveFunction(file, this->_rows);
    file.close();
    return *this;
}

Database::ITable &Database::Table::updateField(const Database::Field &field, const Database::Field &newField)
{
    const Rows::iterator it = this->_rows.find(field);

    if (it != this->_rows.end())
    {
        this->_rows[newField] = it->second;
        this->_rows.erase(it);
    }
    else
        throw std::runtime_error(field + ": not found.");

    return *this;
}

Database::ITable &Database::Table::updateRow(const Database::Row &row)
{
    for (auto &map : this->_rows)
    {
        for (auto &Row : map.second)
        {
            if (Row.first == row.second && row.first.count(map.first) == 1)
                Row.second = row.first.at(map.first);
        }
    }

    return *this;
}

const std::string &Database::Table::getTableName() const
{
    return this->_tableName;
}

Database::ITable &Database::Table::renameTable(const std::string &newTableName)
{
    this->_tableName = newTableName;

    return *this;
}

Database::Row Database::Table::getRow(std::function<bool(Database::Row)> func)
{
    Database::Row row;
    auto max = this->_rows.begin()->second.size();
    std::map<Database::Field, std::vector<std::pair<Database::Id, Database::Data>>> tmpRows;

    for (const auto &field : this->_rows)
        for (const auto &it : field.second)
            tmpRows[field.first].emplace_back(std::make_pair(it.first, it.second));

    unsigned long i = 0;
    while (i < max)
    {
        row.second = tmpRows.begin()->second[i].first;
        for (const auto &field : tmpRows)
        {
            row.first[field.first] = field.second[i].second;
            if (func(row))
                return row;
        }
        i++;
    }

    return Database::Row();
}

std::vector<Database::Row> Database::Table::getRows(std::function<bool(Database::Row)> func)
{
    Database::Row row;
    auto max = this->_rows.begin()->second.size();
    std::map<Database::Field, std::vector<std::pair<Database::Id, Database::Data>>> tmpRows;
    std::vector<Row>    finalRows;

    for (const auto &field : this->_rows)
        for (const auto &it : field.second)
            tmpRows[field.first].emplace_back(std::make_pair(it.first, it.second));

    unsigned long i = 0;
    while (i < max)
    {
        row.second = tmpRows.begin()->second[i].first;
        for (const auto &field : tmpRows)
        {
            row.first[field.first] = field.second[i].second;
            if (func(row))
                finalRows.push_back(row);
        }
        i++;
    }

    return finalRows;
}

Database::ITable &Database::Table::parse(std::function<void(std::ifstream &, Rows &)> func)
{
    std::ifstream file(this->_dbName + "/" + this->_tableName + ".db");
    if (!file.is_open())
    {
        LOG.warning("Table " + _tableName + " save dont exist");
        return *this;
    }
    func(file, this->_rows);
    file.close();
    return *this;
}

Database::ITable &Database::Table::setSaveFunction(std::function<void(std::ofstream &, const Rows &)> func)
{
    _saveFunction = func;
    return *this;
}