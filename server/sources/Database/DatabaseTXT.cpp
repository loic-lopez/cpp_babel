// ██████╗  █████╗ ██████╗     ███████╗██╗          ██████╗ ██╗   ██╗███████╗██████╗
// ██╔══██╗██╔══██╗██╔══██╗    ██╔════╝██║         ██╔═══██╗██║   ██║██╔════╝██╔══██╗
// ██████╔╝███████║██████╔╝    █████╗  ██║         ██║   ██║██║   ██║█████╗  ██║  ██║
// ██╔══██╗██╔══██║██╔══██╗    ██╔══╝  ██║         ██║   ██║██║   ██║██╔══╝  ██║  ██║
// ██████╔╝██║  ██║██████╔╝    ███████╗███████╗    ╚██████╔╝╚██████╔╝███████╗██████╔╝
// ╚═════╝ ╚═╝  ╚═╝╚═════╝     ╚══════╝╚══════╝     ╚═════╝  ╚═════╝ ╚══════╝╚═════╝ 
// DatabaseTXT.cpp created 28/09/2017

#include "DatabaseTXT.hpp"
#include "Table.hpp"

Database::DatabaseTXT::DatabaseTXT(const std::string &databaseName)
{
    this->_databaseName = databaseName;
    boost::filesystem::path path(databaseName);

    if (!boost::filesystem::exists(path))
        boost::filesystem::create_directories(path);
}

Database::DatabaseTXT::~DatabaseTXT()
{

}

//Database::IDatabase &Database::DatabaseTXT::addTable(const std::string &tableName,
//                                                     std::vector<Field> fields, std::function<void (unsigned int, char *, Database::Rows &rows)> func)
//{
//        this->_tables[tableName] = boost::make_shared<ITable *>(new Database::Table(tableName, fields, func, this->_databaseName));
//}

Database::IDatabase &Database::DatabaseTXT::addTable(const std::string &tableName)
{
    try
    {
        if (this->_tables.count(tableName))
            throw Database::ITable::TableAlreadyExist(tableName);

        this->_tables[tableName] = boost::make_shared<ITable *>(new Database::Table(tableName, _databaseName));
        return *this;
    }
    catch (const Database::ITable::TableAlreadyExist &e)
    {
        std::cerr << e.what() << std::endl;
        throw std::exception();
    }
}

Database::ITable *Database::DatabaseTXT::getTable(const std::string &tableName)
{
    const std::map<std::string, boost::shared_ptr<ITable *>>::iterator it = this->_tables.find(tableName);

    if (it != this->_tables.end())
        return *this->_tables[tableName];
    else
        throw std::runtime_error(tableName + ": not found.");
}

Database::IDatabase &Database::DatabaseTXT::loadDatabase()
{
    return *this;
}

Database::IDatabase &Database::DatabaseTXT::print()
{
    return *this;
}

Database::IDatabase &Database::DatabaseTXT::deleteTable(const std::string &tableName)
{
    this->_tables.erase(tableName);

    return *this;
}

Database::IDatabase &Database::DatabaseTXT::renameTable(const std::string &tableName, const std::string &newTableName)
{
    const std::map<std::string, boost::shared_ptr<ITable *>>::iterator it = this->_tables.find(tableName);
    if (it != this->_tables.end())
    {
        this->_tables[newTableName] = it->second;
        (*it->second)->renameTable(newTableName);
        this->_tables.erase(it);
    }
    else
        throw std::runtime_error(tableName + ": not found.");

    return *this;
}

Database::IDatabase &Database::DatabaseTXT::saveTables()
{
    for (auto &it : _tables)
    {
        LOG.log("[TABLE] Saving " + it.first);
        (*it.second.get())->save();
    }
    return *this;
}

Database::IDatabase &Database::DatabaseTXT::addFieldToTable(const Database::Field &field, const std::string &tableName)
{
    (*this->_tables[tableName])->addField(field);
    return *this;
}

Database::IDatabase &Database::DatabaseTXT::setSavefunction(std::function<void(const Database::Rows &)> function)
{
    _saveFunc = function;
    return *this;
}

