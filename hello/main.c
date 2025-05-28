 /*
  * SPDX-FileCopyrightText: 2021 Monaco F. J. <monaco@usp.br>
  * SPDX-FileCopyrightText: 2025 Andrey <andrey.cortez12@gmail.com>
  *
  * SPDX-License-Identifier: GPL-3.0-or-later
  *
  * This file is a derivative of SYSeg (https://gitlab.com/monaco/syseg)
  * and includes modifications made by the following author(s):
  * Andrey <andrey.cortez12@gmail.com>
  */

 // Declaração da função assembly get_conventional_memory_kb
 extern unsigned int get_conventional_memory_kb(void);

 // Declaração da função assembly printf (o nome real da label em libc.S)
 // Não é chamada diretamente como uma função C padrão devido à convenção de chamada.
 extern void printf(void); // Apenas para o linker saber que existe.

 // Wrapper inline assembly para chamar a nossa printf em libc.S corretamente
 static inline void asm_printf(const char *s) {
    __asm__ __volatile__ (
        // O ponteiro 's' já estará em CX devido à constraint "c"(s) abaixo.
        "call printf"        // Chamar a label printf em libc.S
        : /* sem operandos de saída */
        : "c"(s)             // Operando de entrada: s (ponteiro), colocado diretamente em CX pelo GCC.
        : "%ax", "%bx", "%si", "memory", "cc" // Registos modificados pela função printf em assembly:
                                     // ax, bx, si são usados/modificados.
                                     // "memory" indica que a memória pode ser lida/escrita (pela int 0x10).
                                     // "cc" indica que os sinalizadores (flags) são modificados.
    );
 }

 // Função simples para converter um inteiro não assinado para string
 // s deve ser grande o suficiente para conter o número e o terminador nulo.
 // Máx 65535 para unsigned int (16-bit) são 5 dígitos + nulo = 6 caracteres.
 void utoa(unsigned int n, char s[]) {
     int i = 0;
     if (n == 0) {
         s[i++] = '0';
         s[i] = '\0';
         return;
     }

     // Gerar dígitos na ordem inversa
     unsigned int num = n; // Usar uma cópia para não modificar o n original se for preciso depois
     while (num > 0) {
         s[i++] = (num % 10) + '0'; // Obter o próximo dígito
         num /= 10;                 // Removê-lo
     }
     s[i] = '\0'; // Terminar com nulo

     // Inverter a string
     int j;
     char temp;
     // i agora é o comprimento da string (excluindo o nulo, mas é o índice do nulo)
     // então o último caractere está em i-1
     for (j = 0, i--; j < i; j++, i--) {
         temp = s[j];
         s[j] = s[i];
         s[i] = temp;
     }
 }

 int main(void)
 {
   char msg_hello[] = "Hello World!";
   char msg_mem_prefix[] = "Conventional Memory (KB): ";
   char mem_val_str[10]; // Buffer para guardar o tamanho da memória como string
   unsigned int mem_kb;

   asm_printf(msg_hello);
   asm_printf("\n"); // Passa o ponteiro para a string literal "\n" (que é {'\n', '\0'})

   mem_kb = get_conventional_memory_kb(); // Chama a nossa função assembly

   utoa(mem_kb, mem_val_str); // Converte o unsigned int para string

   asm_printf(msg_mem_prefix);
   asm_printf(mem_val_str);
   asm_printf("\n");

   // Loop infinito para parar a execução aqui e ver a saída
   // Em ambientes bare-metal, retornar de main pode ter consequências indefinidas.
   while(1);

   return 0; // Tecnicamente inalcançável devido ao while(1)
 }
