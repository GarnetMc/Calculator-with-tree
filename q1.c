
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define empty(s) (!(s))

typedef struct node{
    char item[8];
    double value;
    struct node *left;
    struct node *right;
} node;

void make_tree(node **toInsert, char *expression);    //creates a tree from a string
void print_pre(node *toPrint);                        //prints in pre order
void print_post(node *toPrint);                       //prints in post order
void print_in(node *toPrint);                         //prints in order
void replace_variable(node *tree, char *name, double new_value);   //changes the value of a variable
double calculate(node *head );                                     //calculates the result of the expression
double do_calculation(double a, double b, char operation);   //does a different calculation depending on the operation char
int tree_size(node *head);                                   //checks the depth of the tree
void print_tree(node *head, int height);                     //prints the tree as a visual
void print_level(node *head, int level_num, int level_hit, int rightmost);    //prints one level of the tree
void print_vars(node *head);                                 //prints the variables and their values
void print_spaces(int a);                                    //formatting for print tree
int power(int base, int exponent);                           //calculates exponentials
void print_commands();                                       //prints a list of commands for the menu

int main(int argc, char *argv[])
{
    node* head;
    char expression[100];
    strcpy(expression, argv[1]);
    make_tree(&head, expression);
    print_commands();
    int choice = 0;
    while (choice != 7)
    {
        printf("Enter a command: ");
        scanf("%d", &choice);
        if (choice == 1)
        {
            int height = tree_size(head);
            height++;
            print_tree(head, height);
            printf("\n");
            print_vars(head);
            printf("\n");

        }
        else if (choice == 2)
        {
            printf("Printing in preorder\n");
            print_pre(head);
            printf("\n");
        }
        else if (choice == 3)
        {
            printf("Printing in order\n");
            print_in(head);
            printf("\n");
        }
        else if (choice == 4)
        {
            printf("Printing in postorder\n");
            print_post(head);
            printf("\n");
        }
        else if (choice == 5)
        {
            char name[10];
            double new_value;
            printf("Enter the name of the variable you want to replance: ");
            scanf("%s", name );
            printf("Enter the value you want to replace it with: ");
            scanf("%lf", &new_value);
            replace_variable(head, name, new_value);
        }
        else if (choice == 6)
        {
            double result = calculate(head);
            if (!isinf(result))
            {
                printf("%.2lf\n", result);
            }
            else{
                printf("error\n");
            }
        }
        else if (choice == 7)
        {
            ;
        }
        else if (choice == 8)
        {
            print_commands();
        }
        else
        {
            printf("I think you entered an invalid command\n");
        }
    }
    return 0;
}

void make_tree(node **toInsert, char *expression)
{
    *toInsert = (node*)malloc(sizeof(node));
    int leftCount = 0;
    int rightCount = 0;
    char left[100];
    char right[100];
    for (int i = 0; i < strlen(expression); i++)
    {
        if (expression[i] == '(')
        {
            leftCount += 1;
        }
        else if (expression[i] == ')')
        {
            rightCount += 1;
        }
        else if ((expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/') && (leftCount - rightCount) == 1)
        {
            memcpy((*toInsert) -> item , &expression[i], 1 );
            (*toInsert)-> item[1] = '\0';
            memcpy(left, &expression[1], i - 1);
            left[i - 1] = '\0';
            memcpy(right, &expression[i+1], strlen(expression) - i - 2);
            right[strlen(expression)-i -2] = '\0';
            make_tree(&(*toInsert) -> left, left);
            make_tree(&(*toInsert) -> right, right);
        }
    }
    if(leftCount == 0 && rightCount == 0)
    {
        memcpy((*toInsert) -> item , &expression[0], strlen(expression));
        (*toInsert) -> item[strlen(expression)] = '\0';
        if ((*toInsert) -> item[0] == 'x')
        {
          (*toInsert) -> value = 0.0;
        }
        else
        {
            (*toInsert) -> value = atof((*toInsert) -> item);

        }
    }
}

void print_pre(node *toPrint)
{
    if (toPrint-> item != NULL)
    {
        printf("%s", toPrint -> item);
        print_pre(toPrint -> left);
        print_pre(toPrint -> right);
    }
    else{
      return ;
    }
}

void print_post(node *toPrint)
{
    if (toPrint-> item != NULL)
    {
        print_post(toPrint -> left);
        print_post(toPrint -> right);
        printf("%s", toPrint -> item);
    }
    else{
        return ;
    }
}

void print_in(node *toPrint)
{
    if (toPrint == NULL)
    {
        return;
    }
    if(toPrint-> left != NULL && toPrint-> right !=NULL)
    {
        printf("(");
    }
    print_in(toPrint-> left);
    printf("%s", toPrint -> item);
    print_in(toPrint-> right);
    if(toPrint-> left != NULL && toPrint-> right !=NULL)
    {
        printf(")");
    }
}

void replace_variable(node *tree, char *name, double new_value)
{
    if (tree-> item != NULL)
    {
        replace_variable(tree -> left, name, new_value);
        replace_variable(tree -> right, name, new_value);
        if (strcmp(tree -> item, name) == 0)
        {
            tree -> value = new_value;
        }
    }
    else{
        return ;
    }
}

double calculate(node *head )
{
    if ((head->left == NULL) && (head->right == NULL))
    {
        return head->value;
    }
    else
    {
        return do_calculation(calculate(head->left), calculate(head->right), head->item[0]);
    }
}

double do_calculation(double a, double b, char operation)   //does a different calculation depending on the operation char
{
    if (operation == '+')
    {
        return a + b;
    }
    else if (operation == '-')
    {
        return a - b;
    }
    else if (operation == '*')
    {
        return a * b;
    }
    else if (operation == '/')
    {
        return a / b;
    }
    else
    {
        return 0;
    }
}

int tree_size(node *head)
{
    if ((head-> right == NULL) || (head-> left == NULL))
    {
        return 0;
    }
    int a = tree_size(head-> right);
    int b = tree_size(head-> left);
    if (a > b)
    {
        return a + 1;
    }
    else
    {
        return b + 1;
    }
}

void print_tree(node *head, int height)
{
    for (int i = height; i > 0; i--)
    {
        if (i>1)
        {
            printf("  ");
        }
        print_level(head, height, i, 1);
    }
}

void print_level(node *head, int level_num, int level_hit, int rightmost)
{
    if (head-> item != NULL)
    {
        if (level_num == level_hit)
        {
            print_spaces(power(2, level_num));
            printf("%-4s", head -> item);
            print_spaces(power(2, level_num)-2);
            if (rightmost == 1)
            {
                printf("\n");
            }
        }
        print_level(head -> left, level_num - 1, level_hit, 0);
        if (rightmost == 1)
        {
            print_level(head -> right, level_num - 1, level_hit, 1);
        }
        else
        {
            print_level(head -> right, level_num - 1, level_hit, 0);
        }
    }
    else{
        return ;
    }
}

void print_spaces(int a)
{
    for (int i = 0; i< a; i++)
    {
        printf(" ");
    }
}
void print_vars(node *head)
{
    if (head-> item != NULL)
    {
        print_vars(head -> left);
        print_vars(head -> right);
        if (head-> item[0] == 'x')
        {
            printf("%s has value: %.2lf\n", head -> item, head-> value);
        }
    }
    else{
        return ;
    }
}

int power(int base, int exponent)
{
    int result = 1;
    for (int i = 1; i < exponent; i++)
    {
        result = result * base;
    }
    return result;
}

void print_commands()
{
    printf("Enter a number from 1 to 8 corresponding to the command you want to enter\n");
    printf("1. Display\n");
    printf("2. Preorder\n");
    printf("3. Inorder\n");
    printf("4. Postorder\n");
    printf("5. Update\n");
    printf("6. Calculate\n");
    printf("7. Exit\n");
    printf("8. Print Commands\n");
}
