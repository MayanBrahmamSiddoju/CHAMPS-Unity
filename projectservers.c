#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <windows.h>
#include <time.h>
#include <process.h>
#define PORT 8080
#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024
#define HASH_TABLE_SIZE 101
struct Client {
    SOCKET socket;
    char username[BUFFER_SIZE];
};
int num_clients = 0;
struct Client clients[MAX_CLIENTS];
int client_colors[] = {
    FOREGROUND_BLUE,
    FOREGROUND_GREEN,
    FOREGROUND_RED,
    FOREGROUND_INTENSITY,
    // Add more colors if needed
};
struct TreeNode {
    char username[BUFFER_SIZE];
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode* client_btree_root = NULL;


struct HashTable {
    char username[BUFFER_SIZE];
    struct Client* client;
};

struct HashTable hash_table[HASH_TABLE_SIZE];

struct ChatNode {
    char message[BUFFER_SIZE];
    struct ChatNode* next;
};

struct ChatHistory {
    char username[BUFFER_SIZE];
    struct ChatNode* head;
    struct ChatHistory* next;
};

struct ChatHistory* individual_chats_head = NULL;
struct ChatNode* group_chat_head = NULL;

void handle_client(SOCKET client_socket);
void broadcast_message(const char* username, const char* message);
void send_prompt(SOCKET client_socket, const char* prompt);
void receive(SOCKET client_socket, char* buffer);
int receive_int(SOCKET client_socket);
void add_client(struct Client client);
void remove_client(SOCKET client_socket);
void send_client_list(SOCKET client_socket);
void insert_into_btree(struct TreeNode** root, const char* username);
struct TreeNode* find_min_node(struct TreeNode* node);
struct TreeNode* delete_from_btree(struct TreeNode* root, const char* username);
void destroy_btree(struct TreeNode* root);
unsigned int hash_function(const char* username);
void display_chat_history(SOCKET client_socket);
void display_chat_history(SOCKET client_socket);
void insert_into_individual_chats(const char* username, const char* message);
void insert_into_group_chat(const char* message);
void send_chat_history(SOCKET client_socket, int history_option);
void remove_last_message(const char* username);
int main() {
    WSADATA wsa;
    SOCKET server_socket, client_socket;
    struct sockaddr_in server, client;

    printf("Initializing Winsock...\n");
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Failed. Error Code : %d", WSAGetLastError());
        return 1;
    }

    printf("Winsock initialized.\n");

    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Could not create socket : %d", WSAGetLastError());
    }

    printf("Socket created.\n");

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
        printf("Bind failed with error code : %d", WSAGetLastError());
        exit(EXIT_FAILURE);
    }

    puts("Bind done");

    listen(server_socket, 3);

    puts("Waiting for incoming connections...");

    while (1) {
        int client_size = sizeof(struct sockaddr_in);
        client_socket = accept(server_socket, (struct sockaddr*)&client, &client_size);
        if (client_socket == INVALID_SOCKET) {
            printf("Accept failed with error code : %d", WSAGetLastError());
            exit(EXIT_FAILURE);
        }

        printf("Connection accepted.\n");

        // Handle the client in a separate thread
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)handle_client, (LPVOID)client_socket, 0, NULL);
    }

    closesocket(server_socket);
    WSACleanup();

    return 0;
}

void handle_client(SOCKET client_socket) {
    // Prompt the client to enter a username
    send_prompt(client_socket, "Enter username: ");
    char username[BUFFER_SIZE];
    receive(client_socket, username);

    // Add the client to the list
    struct Client new_client;
    new_client.socket = client_socket;
    strncpy(new_client.username, username, sizeof(new_client.username));
    add_client(new_client);
    
    // Assign a color to the client based on their index
    int client_color = client_colors[num_clients % (sizeof(client_colors) / sizeof(int))];

    // Send the welcome message to the client
    char welcome_message[BUFFER_SIZE];
    snprintf(welcome_message, sizeof(welcome_message), "Welcome, %s!\n", username);
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), client_color);
	send(client_socket, welcome_message, strlen(welcome_message), 0);
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
    // Send the list of connected clients to the client
    send_client_list(client_socket);

    // Notify other clients about the new client
    char new_client_message[BUFFER_SIZE];
    snprintf(new_client_message, sizeof(new_client_message), "%s has joined the chat.\n", username);
    broadcast_message("SERVER", new_client_message);

    int option;
    do {
        // Prompt the client with available options
        send_prompt(client_socket, "Choose an option:\n1. Broadcast message\n2. Private message\n3. Exit\n4. History\n");

        // Receive the client's option
        option = receive_int(client_socket);

        if (option == 1) {
            // Broadcast message
            // ... (Previous code for broadcasting message)
             while (1) {
                send_prompt(client_socket, "Enter your message (or type 'exit' to go back to options): ");
                char buffer[BUFFER_SIZE] = { '\0' };
                receive(client_socket, buffer);

                if (strcmp(buffer, "exit") != 0) {
                    // Broadcast the message with username and timestamp
                     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), client_color);
            broadcast_message(username, buffer);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
                }
                else if (strcmp(buffer, "exit") == 0) {
                    break;
                }
            }
        }
        else if (option == 2) {
            // Private message
            // ... (Previous code for private message)
            while (1) {
                send_prompt(client_socket, "Enter the username of the client you want to communicate with (or type 'exit' to go back to options): ");
                char target_username[BUFFER_SIZE];
                receive(client_socket, target_username);

                if (strcmp(target_username,"exit")!= 0) {
                    // Find the target client
                    struct Client* target_client = NULL;
                    for (int i = 0; i < num_clients; i++) {
                        if (strcmp(clients[i].username, target_username) == 0) {
                            target_client = &clients[i];
                            break;
                        }
                    }

                    if (target_client != NULL && target_client->socket != client_socket) {
                        send_prompt(client_socket, "Enter your message: ");
                        char buffer[BUFFER_SIZE];
                        receive(client_socket, buffer);

                        // Get the current timestamp
                        time_t current_time;
                        time(&current_time);
                        struct tm* time_info = localtime(&current_time);
                        char timestamp[BUFFER_SIZE];
                        strftime(timestamp, sizeof(timestamp), "[%Y-%m-%d %H:%M:%S]", time_info);

                        // Combine timestamp, username, and message
                        char message_with_info[BUFFER_SIZE];
                        snprintf(message_with_info, sizeof(message_with_info), "%s %s: %s", timestamp, username, buffer);

                        // Send the private message to the target client
                         SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), client_color);
            send(target_client->socket, message_with_info, strlen(message_with_info), 0);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
					    //send(target_client->socket, message_with_info, strlen(message_with_info), 0);
                    }
                    
                    else {
                        send_prompt(client_socket, "Invalid target client\n");
                    }
                }
                else if (strcmp(target_username, "exit") == 0)  {
                    break;
                }
            }
        }
        else if (option == 3) {
            // Exit
            // ... (Previous code for exiting)
            break;
        }
        else if (option == 4) {
            // Display chat history
            // ... (Previous code for displaying chat history)
        //display_chat_history(client_socket);
        int history_option;
        send_prompt(client_socket, "1 for Individual chat History\n2 for Group chat History");
        history_option = receive_int(client_socket);
        send_chat_history(client_socket,history_option);
		}
        else {
            send_prompt(client_socket, "Invalid option\n");
        }
    } while (option != 3);

    // Notify other clients about the disconnected client
    char disconnect_message[BUFFER_SIZE];
    snprintf(disconnect_message, sizeof(disconnect_message), "%s has left the chat.\n", username);
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), client_color);
	broadcast_message("SERVER", disconnect_message);
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
    // Remove the client from the list
    remove_client(client_socket);

    // Close the client socket
    closesocket(client_socket);
}

void broadcast_message(const char* sender_username, const char* message) {
    time_t current_time;
    time(&current_time);
    struct tm* time_info = localtime(&current_time);
    char timestamp[BUFFER_SIZE];
    strftime(timestamp, sizeof(timestamp), "[%Y-%m-%d %H:%M:%S]", time_info);

    // Check if the message is a delete command
    if (strcmp(message, "delete") == 0) {
        // Remove the most recent message sent by this client from the chat history
        remove_last_message(sender_username);
        return; // Do not broadcast the "delete" command itself
    }

    // Combine username, timestamp, and message
    char message_with_info[BUFFER_SIZE];
    snprintf(message_with_info, sizeof(message_with_info), "%s %s: %s", timestamp, sender_username, message);

    // Add the message to the group chat history
    insert_into_group_chat(message_with_info);

    // Add the message to individual chat history
    struct ChatHistory* current_chat = individual_chats_head;
    while (current_chat != NULL) {
        if (strcmp(current_chat->username, sender_username) == 0) {
            // Skip adding the message to the sender's individual chat history
            break;
        }
        current_chat = current_chat->next;
    }

    // Broadcast the message to all other connected clients
    for (int i = 0; i < num_clients; i++) {
        if (strcmp(clients[i].username, sender_username) != 0) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), client_colors[i % (sizeof(client_colors) / sizeof(int))] | FOREGROUND_INTENSITY);
            send(clients[i].socket, message_with_info, strlen(message_with_info), 0);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
			//send(clients[i].socket, message_with_info, strlen(message_with_info), 0);
        }
    }
}


void send_prompt(SOCKET client_socket, const char* prompt) {
    send(client_socket, prompt, strlen(prompt), 0);
}

void receive(SOCKET client_socket, char* buffer) {
    recv(client_socket, buffer, BUFFER_SIZE, 0);
}

int receive_int(SOCKET client_socket) {
    char buffer[BUFFER_SIZE];
    receive(client_socket, buffer);
    return atoi(buffer);
}

void add_client(struct Client client) {
    // ... (Previous code for adding a client)
    if (num_clients < MAX_CLIENTS) {
        clients[num_clients] = client;
        num_clients++;
        insert_into_btree(&client_btree_root, client.username);
        unsigned int hash_value = hash_function(client.username) % HASH_TABLE_SIZE;
        strncpy(hash_table[hash_value].username, client.username, sizeof(hash_table[hash_value].username));
        hash_table[hash_value].client = &clients[num_clients - 1];
    }    
}

void remove_client(SOCKET client_socket) {
    // ... (Previous code for removing a client)
     for (int i = 0; i < num_clients; i++) {
        if (clients[i].socket == client_socket) {
            for (int j = i; j < num_clients - 1; j++) {
                clients[j] = clients[j + 1];
            }
            num_clients--;
            break;
        }
    }
}

void send_client_list(SOCKET client_socket) {
    // ... (Previous code for sending the client list)
     send_prompt(client_socket, "Connected Clients:\n");

    for (int i = 0; i < num_clients; i++) {
        send(client_socket, clients[i].username, strlen(clients[i].username), 0);
        send(client_socket, "\n", 1, 0);
    }
}

void insert_into_btree(struct TreeNode** root, const char* username) {
    // ... (Previous code for inserting into the binary search tree)
    if (*root == NULL) {
        root = (struct TreeNode )malloc(sizeof(struct TreeNode));
        strncpy((*root)->username, username, sizeof((*root)->username));
        (*root)->left = NULL;
        (*root)->right = NULL;
    }
    else {
        int compare_result = strcmp(username, (*root)->username);
        if (compare_result < 0) {
            insert_into_btree(&((*root)->left), username);
        }
        else if (compare_result > 0) {
            insert_into_btree(&((*root)->right), username);
        }
    }
}

struct TreeNode* find_min_node(struct TreeNode* node) {
    // ... (Previous code for finding the minimum node in the binary search tree)
    if (node->left == NULL) {
        return node;
    }
    return find_min_node(node->left);
}

struct TreeNode* delete_from_btree(struct TreeNode* root, const char* username) {
    // ... (Previous code for deleting from the binary search tree)
    if (root == NULL) {
        return root;
    }

    int compare_result = strcmp(username, root->username);
    if (compare_result < 0) {
        root->left = delete_from_btree(root->left, username);
    }
    else if (compare_result > 0) {
        root->right = delete_from_btree(root->right, username);
    }
    else {
        if (root->left == NULL) {
            struct TreeNode* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct TreeNode* temp = root->left;
            free(root);
            return temp;
        }

        struct TreeNode* temp = find_min_node(root->right);
        strncpy(root->username, temp->username, sizeof(root->username));
        root->right = delete_from_btree(root->right, temp->username);
    }
    return root;
}

void destroy_btree(struct TreeNode* root) {
    // ... (Previous code for destroying the binary search tree)
     if (root != NULL) {
        destroy_btree(root->left);
        destroy_btree(root->right);
        free(root);
    }
}

unsigned int hash_function(const char* username) {
    // ... (Previous code for the hash function)
     unsigned int hash = 5381;
    int c;

    while ((c = *username++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    return hash;
}

void insert_into_individual_chats(const char* username, const char* message) {
    // ... (Previous code for inserting into individual chat history)
    struct ChatHistory* current_chat = individual_chats_head;
    while (current_chat != NULL) {
        if (strcmp(current_chat->username, username) == 0) {
            struct ChatNode* new_node = (struct ChatNode*)malloc(sizeof(struct ChatNode));
            strncpy(new_node->message, message, sizeof(new_node->message));
            new_node->next = NULL;

            if (current_chat->head == NULL) {
                current_chat->head = new_node;
            }
            else {
                struct ChatNode* last_node = current_chat->head;
                while (last_node->next != NULL) {
                    last_node = last_node->next;
                }
                last_node->next = new_node;
            }
            break;
        }
        current_chat = current_chat->next;
    }
}

void insert_into_group_chat(const char* message) {
    // Insert the message at the beginning of the group chat history
    struct ChatNode* new_message = (struct ChatNode*)malloc(sizeof(struct ChatNode));
    strncpy(new_message->message, message, sizeof(new_message->message));
    new_message->next = group_chat_head;
    group_chat_head = new_message;
}
void send_chat_history(SOCKET client_socket, int history_option) {
    if (history_option == 1) {
        // Send individual chat history
        send_prompt(client_socket, "Individual Chat History:\n");

        // Send individual chat history to the client
        struct ChatHistory* current_chat = individual_chats_head;
        while (current_chat != NULL) {
            send_prompt(client_socket, "Chat history with ");
            send(client_socket, current_chat->username, strlen(current_chat->username), 0);
            send(client_socket, ":\n", 2, 0);

            struct ChatNode* current_node = current_chat->head;
            while (current_node != NULL) {
                send(client_socket, current_node->message, strlen(current_node->message), 0);
                send(client_socket, "\n", 1, 0);
                current_node = current_node->next;
            }

            current_node = current_chat->head;
        while (current_node != NULL) {
            // Skip deleted messages
            if (strncmp(current_node->message, "DELETED: ", 9) != 0) {
                send(client_socket, current_node->message, strlen(current_node->message), 0);
                send(client_socket, "\n", 1, 0);
            }
            current_node = current_node->next;
            current_chat = current_chat->next;
        }
    }}
    else if (history_option == 2) {
        // Send group chat history
        send_prompt(client_socket, "Group Chat History:\n");

        // Send group chat history to the client
        struct ChatNode* current_node = group_chat_head;
        while (current_node != NULL) {
        	if (strncmp(current_node->message, "DELETED: ", 9) != 0) {
            send(client_socket, current_node->message, strlen(current_node->message), 0);
            send(client_socket, "\n", 1, 0);}
            current_node = current_node->next;
        }
        current_node = group_chat_head;
        while (current_node != NULL) {
            // Skip deleted messages
            if (strncmp(current_node->message, "DELETED: ", 9) != 0) {
                send(client_socket, current_node->message, strlen(current_node->message), 0);
                send(client_socket, "\n", 1, 0);
            }
            current_node = current_node->next;
    }}

    // Send a special message to indicate the end of the chat history
   // send(client_socket, "END_HISTORY", strlen("END_HISTORY"), 0);
    else
    {
    	return;
	}
}
void remove_last_message(const char* username) {
    // Find the individual chat history for the specified client
    struct ChatHistory* current_chat = individual_chats_head;
    while (current_chat != NULL) {
        if (strcmp(current_chat->username, username) == 0) {
            // Delete the most recent message from the chat history
            struct ChatNode* last_node = current_chat->head;
            if (last_node != NULL) {
                if (last_node->next == NULL) {
                    // The client has only one message in the chat history
                    free(last_node);
                    current_chat->head = NULL;
                } else {
                    // Traverse to the second-to-last node in the chat history
                    while (last_node->next->next != NULL) {
                        last_node = last_node->next;
                    }
                    free(last_node->next);
                    last_node->next = NULL;
                }
            }
            break;
        }
        current_chat = current_chat->next;
    }
}