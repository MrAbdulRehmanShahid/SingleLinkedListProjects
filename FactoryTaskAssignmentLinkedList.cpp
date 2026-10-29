#include <iostream>
#include <limits>
using namespace std;

// Each node stores one factory task.
struct FactoryTaskNode
{
    int taskID;
    string title;
    string workerID;
    int priority;       // 1 = High, 2 = Medium, 3 = Low
    string status;      // Pending, In Progress, Completed
    FactoryTaskNode* next;
};

class FactoryTaskList
{
private:
    FactoryTaskNode* head;
    int count;
    FactoryTaskNode* GetNodeAt(int index) const
    {
        FactoryTaskNode* current = head;

        for (int i = 0; i < index && current != NULL; i++)
            current = current->next;

        return current;
    }
    void CopyTaskData(FactoryTaskNode* first, FactoryTaskNode* second)
    {
        swap(first->taskID, second->taskID);
        swap(first->title, second->title);
        swap(first->workerID, second->workerID);
        swap(first->priority, second->priority);
        swap(first->status, second->status);
    }

    void ClearInputLine()
    {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

public:
    FactoryTaskList()
    {
        head = NULL;
        count = 0;
    }

    bool IsEmpty() const
    {
        return head == NULL;
    }

    bool IsNotEmpty() const
    {
        return head != NULL;
    }

    int GetCount() const
    {
        return count;
    }

    // Insert a task at the head of the list.
    void Insert(FactoryTaskNode* task)
    {
        if (task == NULL)
            return;

        task->next = head;
        head = task;
        count++;
    }

    // Remove and return the first task. Caller must delete it.
    FactoryTaskNode* Remove()
    {
        if (IsEmpty())
            return NULL;

        FactoryTaskNode* task = head;
        head = head->next;
        task->next = NULL;
        count--;

        return task;
    }

    // Insert at a zero-based index. Out-of-range indexes are clamped.
    void InsertAt(FactoryTaskNode* task, int index)
    {
        if (task == NULL)
            return;

        if (index < 0)
            index = 0;
        if (index > count)
            index = count;

        if (index == 0)
        {
            Insert(task);
            return;
        }

        FactoryTaskNode* previous = GetNodeAt(index - 1);
        task->next = previous->next;
        previous->next = task;
        count++;
    }

    // Remove and return a task at a zero-based index. Caller must delete it.
    FactoryTaskNode* RemoveAt(int index)
    {
        if (IsEmpty())
            return NULL;

        if (index < 0)
            index = 0;
        if (index >= count)
            index = count - 1;

        if (index == 0)
            return Remove();

        FactoryTaskNode* previous = GetNodeAt(index - 1);
        FactoryTaskNode* task = previous->next;

        previous->next = task->next;
        task->next = NULL;
        count--;

        return task;
    }

    // Exchange task data at two valid indexes.
    void Swap(int index1, int index2)
    {
        if (index1 < 0 || index1 >= count ||
            index2 < 0 || index2 >= count ||
            index1 == index2)
            return;

        CopyTaskData(GetNodeAt(index1), GetNodeAt(index2));
    }

    void Sort()
    {
        for (FactoryTaskNode* i = head; i != NULL; i = i->next)
        {
            for (FactoryTaskNode* j = i->next; j != NULL; j = j->next)
            {
                if (i->priority > j->priority)
                    CopyTaskData(i, j);
            }
        }
    }

    // Reverse the node links.
    void Reverse()
    {
        FactoryTaskNode* previous = NULL;
        FactoryTaskNode* current = head;
        FactoryTaskNode* nextNode = NULL;

        while (current != NULL)
        {
            nextNode = current->next;
            current->next = previous;
            previous = current;
            current = nextNode;
        }

        head = previous;
    }

    void Print() const
    {
        if (IsEmpty())
        {
            cout << "\nNo factory tasks are currently stored.\n";
            return;
        }

        FactoryTaskNode* current = head;
        int index = 0;

        cout << "\nIndex\tTask ID\tWorker ID\tPriority\tStatus\t\tTitle\n";
        cout << "--------------------------------------------------------------------------\n";

        while (current != NULL)
        {
            string priorityText;

            if (current->priority == 1)
                priorityText = "High";
            else if (current->priority == 2)
                priorityText = "Medium";
            else if (current->priority == 3)
                priorityText = "Low";
            else
                priorityText = "Other";

            cout << index << '\t'
                 << current->taskID << '\t'
                 << current->workerID << "\t\t"
                 << priorityText << "\t\t"
                 << current->status << "\t"
                 << current->title << '\n';

            current = current->next;
            index++;
        }

        cout << "Total tasks: " << count << '\n';
    }

    // Release every node when the list is destroyed.
    ~FactoryTaskList()
    {
        while (!IsEmpty())
            delete Remove();
    }
};

// Create and initialize a new task node.
FactoryTaskNode* CreateTask(int id, const string& title,
                            const string& workerID, int priority,
                            const string& status)
{
    FactoryTaskNode* task = new FactoryTaskNode;
    task->taskID = id;
    task->title = title;
    task->workerID = workerID;
    task->priority = priority;
    task->status = status;
    task->next = NULL;
    return task;
}

int ReadInt(const string& prompt)
{
    int value;

    while (true)
    {
        cout << prompt;
        if (cin >> value)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }

        cout << "Invalid input. Please enter a whole number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

FactoryTaskNode* ReadTask()
{
    int id = ReadInt("Enter Task ID: ");

    string title;
    cout << "Enter task title: ";
    getline(cin, title);

    string workerID;
    cout << "Enter Worker ID (e.g., W01): ";
    getline(cin, workerID);

    int priority;
    do
    {
        priority = ReadInt("Enter priority (1=High, 2=Medium, 3=Low): ");
        if (priority < 1 || priority > 3)
            cout << "Priority must be 1, 2, or 3.\n";
    } while (priority < 1 || priority > 3);

    int statusChoice;
    do
    {
        cout << "Choose status: 1. Pending  2. In Progress  3. Completed\n";
        statusChoice = ReadInt("Enter status choice: ");
        if (statusChoice < 1 || statusChoice > 3)
            cout << "Choose 1, 2, or 3.\n";
    } while (statusChoice < 1 || statusChoice > 3);

    string status;
    if (statusChoice == 1)
        status = "Pending";
    else if (statusChoice == 2)
        status = "In Progress";
    else
        status = "Completed";

    return CreateTask(id, title, workerID, priority, status);
}

void DisplayMenu()
{
    cout << "\n========================================\n";
    cout << " FACTORY TASK ASSIGNMENT MANAGER\n";
    cout << "========================================\n";
    cout << "1.  Display all tasks\n";
    cout << "2.  Insert task at head\n";
    cout << "3.  Remove task from head\n";
    cout << "4.  Insert task at index\n";
    cout << "5.  Remove task at index\n";
    cout << "6.  Swap tasks\n";
    cout << "7.  Sort tasks by priority\n";
    cout << "8.  Reverse task list\n";
    cout << "9.  Check collection status\n";
    cout << "10. Add sample tasks\n";
    cout << "11. Exit\n";
}

void AddSampleTasks(FactoryTaskList& tasks)
{
    tasks.InsertAt(CreateTask(101, "Inspect conveyor belt", "W03", 1, "Pending"), tasks.GetCount());
    tasks.InsertAt(CreateTask(102, "Package finished goods", "W01", 3, "In Progress"), tasks.GetCount());
    tasks.InsertAt(CreateTask(103, "Repair cutting machine", "W02", 1, "Pending"), tasks.GetCount());
    tasks.InsertAt(CreateTask(104, "Check product quality", "W04", 2, "Completed"), tasks.GetCount());

    cout << "Sample tasks added.\n";
}

int main()
{
    FactoryTaskList tasks;
    int choice;

    do
    {
        DisplayMenu();
        choice = ReadInt("Enter your choice: ");

        switch (choice)
        {
            case 1:
                tasks.Print();
                break;

            case 2:
                tasks.Insert(ReadTask());
                cout << "Task inserted at the head.\n";
                break;

            case 3:
            {
                FactoryTaskNode* removed = tasks.Remove();

                if (removed == NULL)
                    cout << "The task list is empty.\n";
                else
                {
                    cout << "Removed task: " << removed->taskID
                         << " - " << removed->title << '\n';
                    delete removed;
                }
                break;
            }

            case 4:
            {
                FactoryTaskNode* task = ReadTask();
                int index = ReadInt("Enter insertion index (starting at 0): ");
                tasks.InsertAt(task, index);
                cout << "Task inserted.\n";
                break;
            }

            case 5:
            {
                int index = ReadInt("Enter removal index (starting at 0): ");
                FactoryTaskNode* removed = tasks.RemoveAt(index);

                if (removed == NULL)
                    cout << "The task list is empty.\n";
                else
                {
                    cout << "Removed task: " << removed->taskID
                         << " - " << removed->title << '\n';
                    delete removed;
                }
                break;
            }

            case 6:
            {
                if (tasks.IsEmpty())
                {
                    cout << "No tasks to swap.\n";
                    break;
                }

                int first = ReadInt("Enter first index: ");
                int second = ReadInt("Enter second index: ");

                if (first < 0 || first >= tasks.GetCount() ||
                    second < 0 || second >= tasks.GetCount())
                    cout << "Invalid index. No swap performed.\n";
                else
                {
                    tasks.Swap(first, second);
                    cout << "Task data swapped.\n";
                }
                break;
            }

            case 7:
                tasks.Sort();
                cout << "Tasks sorted by priority (High to Low urgency number).\n";
                break;

            case 8:
                tasks.Reverse();
                cout << "Task list reversed.\n";
                break;

            case 9:
                if (tasks.IsEmpty())
                    cout << "The task list is empty.\n";
                else
                    cout << "The task list contains " << tasks.GetCount()
                         << " task(s).\n";
                break;

            case 10:
                AddSampleTasks(tasks);
                break;

            case 11:
                cout << "Exiting Factory Task Assignment Manager.\n";
                break;

            default:
                cout << "Invalid choice. Please choose 1 to 11.\n";
        }
    } while (choice != 11);

    return 0;
}
