// DatabaseHandler.h
#pragma once
#include <sqlite3.h>
#include <string>
#include <vector>
#include <map>
using namespace std;

class DatabaseUtil {
    static sqlite3* sqliteDB;
    static bool isConnEstablished;
    static bool isPostgresDBConnEnabled;
    static bool isSqliteDBConnEnabled;

public:
    static const std::string SERVER_DB_FILE_NAME;
    static const std::string CLIENT_DB_FILE_NAME;

    static void Initialize();
    static bool AuthenticateUser(const std::string& username, const std::string& password);
    static int GetUserId(const std::string& username);
    static void EstablishDBConnection(const std::string& a_dbFileName);
    static void UpdateTable(const std::string& username, const std::string& password);
    static void CloseDBConnection();
    static std::string GetBackupPath(int userId, const std::string& filename);
    static void LogOperation(int userId, const std::string& operation);
    static bool DeleteBackup(int userId, const std::string& filename);
    static std::vector<std::string> ListBackups(int userId);
    static bool SaveBackupMetadata(int userId, const std::string& filename, const std::string& filepath);
    static std::map<int, std::map<std::string, std::string>> Execquery(const std::string& query);
    static void InitializeDatabase();
};