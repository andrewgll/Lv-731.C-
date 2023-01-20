#include <iostream>
#include "RootFolder.h"
#include "StatisticManager.h"
#include "ThreadPool.h"
#include "LinesCounter.h"

using namespace std;

//C:\\Users\\l\\source\\repos\\Threads\\
//C:\\Users\\l\\source\\repos\\Testing\\

int main() {
    RootFolder root;
    root.getFilesByExpansions();

    for (auto i = 0; i < root.root_path_files.size(); i++) {
        cout << root.root_path_files[i] << endl;
    }

    StatisticManager statistics;
    ThreadPool thread_pool;
    vector<thread> threads;
    thread_pool.Start(thread_pool, threads);

    for (auto i = 0; i < root.root_path_files.size(); i++)
    {
        thread_pool.QueueJob([](string* file, StatisticManager* statistics)
            {
                statistics->AnalyseLines(Counter(*file));
            }, &root.root_path_files[i], &statistics);
    }
    thread_pool.Stop();
    thread_pool.busy(threads);
    statistics.FileWriter(statistics, root);
    
    return 0;
}
