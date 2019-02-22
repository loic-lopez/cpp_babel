// ██████╗  █████╗ ██████╗     ███████╗██╗          ██████╗ ██╗   ██╗███████╗██████╗ 
// ██╔══██╗██╔══██╗██╔══██╗    ██╔════╝██║         ██╔═══██╗██║   ██║██╔════╝██╔══██╗
// ██████╔╝███████║██████╔╝    █████╗  ██║         ██║   ██║██║   ██║█████╗  ██║  ██║
// ██╔══██╗██╔══██║██╔══██╗    ██╔══╝  ██║         ██║   ██║██║   ██║██╔══╝  ██║  ██║
// ██████╔╝██║  ██║██████╔╝    ███████╗███████╗    ╚██████╔╝╚██████╔╝███████╗██████╔╝
// ╚═════╝ ╚═╝  ╚═╝╚═════╝     ╚══════╝╚══════╝     ╚═════╝  ╚═════╝ ╚══════╝╚═════╝ 
// TestAddTable.cpp created 29/09/2017

#include <gtest/gtest.h>
#include "DatabaseTXT.hpp"

TEST(ADD_TABLE_TO_DATABASE, TEST_ADD_TABLE)
{
    Database::IDatabase *database = new Database::DatabaseTXT();

    database->addTable("Username");
    std::string tableName = database->getTable("Username")->getTableName();

    ASSERT_EQ(tableName, "Username");

}

TEST(TABLE_EXISTS_TO_DATABASE, TEST_ADD_TABLE)
{
    Database::IDatabase *database = new Database::DatabaseTXT();

    database->addTable("Username");
    ASSERT_THROW(database->addTable("Username"), std::exception);
}