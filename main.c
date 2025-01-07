#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define PASSWORD_SIZE 3 // tamanho da senha
#define MAX_DIGIT_AMOUNT 3 // quantidade de digitos da senha
#define EXTRA_BUFFER_SIZE 100 // quantidade de caracteres extras para evitar buffer overflow

int PASSWORD[PASSWORD_SIZE] = {4, 2, 9};
const int MAX_INPUT_SIZE = MAX_DIGIT_AMOUNT + EXTRA_BUFFER_SIZE + 1; // quantidade máxima de caracteres que o input pode ter + 1 para o caracter de termino de string

void get_valid_user_input(char *buffer, int max_input_size);
void load_password(char *buffer, int *input_password_buffer, int password_size);
bool is_correct_password(int *input_password, int *password, int password_size);
void handle_incorrect_password(int *input_password, int *password, int password_size);

int main()
{
    char input[MAX_INPUT_SIZE]; // cria o buffer para armazenar o input da senha
    int input_password[PASSWORD_SIZE];
    bool is_safe_opened = false;

    do 
    {
        get_valid_user_input(input, MAX_INPUT_SIZE); // recebe e garante que o input é válido

        load_password(input, input_password, PASSWORD_SIZE); // carrega o input para um array de inteiros

        if (is_correct_password(input_password, PASSWORD, PASSWORD_SIZE))
        {
            break;
        }

        handle_incorrect_password(input_password, PASSWORD, PASSWORD_SIZE);
        
    }
    while (!is_safe_opened);

    printf("Cofre aberto! Parabéns!\n");

}


void _get_user_input(char *buffer, int max_input_size)
{
    printf("Digite a combinação de 3 dígitos para abrir o cofre: ");
    fgets(buffer, max_input_size, stdin);
}

bool have_right_digits_amount(char *input, int input_size, int max_allowed_digits)
{
    int digit_counter = 0;

    for (int i = 0; i < input_size; i++)
    {
        if (input[i] == '\0' || input[i] == '\n')
        {
            break;
        }

        if (isdigit(input[i]))
        {
            digit_counter++;
        }
        else if (input[i] != ' ')
        {
            return false;
        }
    }

    return digit_counter == max_allowed_digits;
}

void get_valid_user_input(char *buffer, int max_input_size)
{
    bool is_valid_input = false;

    do
    {
        _get_user_input(buffer, max_input_size);
        printf("\n");
        is_valid_input = have_right_digits_amount(buffer, max_input_size, MAX_DIGIT_AMOUNT);

        if (!is_valid_input)
        {
            printf("por favor, digite 3 digitos entre 0 e 9. Exemplo '1 3 5'\n");
        }

    } while (!is_valid_input);
}

void load_password(char *buffer, int *input_password_buffer, int password_size)
{
    int buffer_index = 0;
    int input_password_index = 0;

    // itera por todo o buffer até o final da string
    while (buffer[buffer_index] != '\0')
    {
        // verifica se o caracter atual é um digito
        if (isdigit(buffer[buffer_index]))
        {
            // realiza uma operação usando aritimetica de caracteres com base na tabela ASCII
            // para converter o caracter para um inteiro sem precisar de uma função de conversão
            input_password_buffer[input_password_index] = buffer[buffer_index] - '0';
            input_password_index++;
        }
        buffer_index++;
    }
}

bool is_correct_password(int *input_password, int *password, int password_size)
{
    bool is_correct_password = true;

    for (int i = 0; i < password_size; i++)
    {   
        if (input_password[i] != password[i])
        {
            is_correct_password = false;
            break;
        }
    }

    return is_correct_password;
}

bool is_present_in_password(int digit, int *password, int password_size)
{
    for (int i = 0; i < password_size; i++)
    {
        if (digit == password[i])
        {
            return true;
        }
    }

    return false;
}

bool is_in_correct_position(int digit, int *password, int password_size, int position)
{
    return digit == password[position];
}

void handle_incorrect_password(int *input_password, int *password, int password_size) {
    
    for (int i = 0; i < password_size; i++)
    {
        if (is_present_in_password(input_password[i], password, password_size))
        {
            if (is_in_correct_position(input_password[i], password, password_size, i))
            {
                printf("O dígito %d está correto e na posição %d.\n", input_password[i], i + 1);
            }
            else 
            {
                printf("O dígito %d está correto, mas na posição errada.\n", input_password[i]);
            }
        }
        else 
        {
            printf("O dígito %d não faz parte da senha.\n", input_password[i]);
        }
    }

    printf("\n");
}