#include "filaDePrioridade.c"

/* Para este conjunto de testes, os IDs validos
   vao de 0 (zero) a quatro, pois MAX vale 5   */
int main() {
  PFILA f = criarFila();
  float var1, var2, var3, var4; //variáveis para a consulta de prioridade

  exibirLog(f);
  printf("--- INSERÇÃO\n");
  if(inserirElemento(f, 1, 1)) printf("ok\n");
  else printf("nok (1)\n");
  exibirLog(f);
  if(inserirElemento(f, 3, 3)) printf("ok\n");
  else printf("nok (2)\n");
  exibirLog(f);
  if(inserirElemento(f, 2, 2)) printf("ok\n");
  else printf("nok (3)\n");
  exibirLog(f);
  if(inserirElemento(f, 0, 0)) printf("ok\n");
  else printf("nok (4)\n");
  exibirLog(f);
  if(inserirElemento(f, 5, 5)) printf("ok\n");
  else printf("nok (5)\n");
  exibirLog(f);

  printf("--- CONSULTA PRIORIDADE\n");
  exibirLog(f);
  if(consultarPrioridade(f, 1, &var1)) printf("ok - prioridade id %i eh %f\n", 1, var1);
  else printf("nok\n");
  if(consultarPrioridade(f, 3, &var2)) printf("ok - prioridade id %i eh %f\n", 3, var2);
  else printf("nok\n");
  if(consultarPrioridade(f, 2, &var3)) printf("ok - prioridade id %i eh %f\n", 2, var3);
  else printf("nok\n");
  if(consultarPrioridade(f, 0, &var4)) printf("ok - prioridade id %i eh %f\n", 0, var4);
  else printf("nok\n");
  
  printf("\n\n--- AUMENTAR PRIORIDADE\n");
  if(aumentarPrioridade(f, 5, 10)) printf("ok\n");
  else printf("nok (6)\n");
  exibirLog(f);
  if(aumentarPrioridade(f, 0, 15)) printf("ok\n");
  else printf("nok (7)\n");
  exibirLog(f);
  if(aumentarPrioridade(f, 3, 4)) printf("ok\n");
  else printf("nok (8)\n");
  exibirLog(f);
  if(aumentarPrioridade(f, 3, 4)) printf("ok\n");
  else printf("nok (9) - esperado, pois a nova prioridade nao eh maior\n");
  exibirLog(f);
  if(aumentarPrioridade(f, 4, 4)) printf("ok\n");
  else printf("nok (10) - esperado, elemento com id=4 nao existe\n");
  exibirLog(f);

  printf("--- CONSULTA PRIORIDADE\n");
  exibirLog(f);
  if(consultarPrioridade(f, 1, &var1)) printf("ok - prioridade id %i eh %f\n", 1, var1);
  else printf("nok\n");
  if(consultarPrioridade(f, 3, &var2)) printf("ok - prioridade id %i eh %f\n", 3, var2);
  else printf("nok\n");
  if(consultarPrioridade(f, 2, &var3)) printf("ok - prioridade id %i eh %f\n", 2, var3);
  else printf("nok\n");
  if(consultarPrioridade(f, 0, &var4)) printf("ok - prioridade id %i eh %f\n", 0, var4);
  else printf("nok\n");
  
  printf("\n\n--- REMOÇÃO\n");
  PONT prioritario;
  prioritario = removerElemento(f);
  if (prioritario) printf("Prioritario: %i, %f\n", prioritario->id, prioritario->prioridade);
  else printf("Fila vazia (1)\n");
  exibirLog(f);
  prioritario = removerElemento(f);
  if (prioritario) printf("Prioritario: %i, %f\n", prioritario->id, prioritario->prioridade);
  else printf("Fila vazia (2)\n");
  exibirLog(f);
  prioritario = removerElemento(f);
  if (prioritario) printf("Prioritario: %i, %f\n", prioritario->id, prioritario->prioridade);
  else printf("Fila vazia (3)\n");
  exibirLog(f);
  prioritario = removerElemento(f);
  if (prioritario) printf("Prioritario: %i, %f\n", prioritario->id, prioritario->prioridade);
  else printf("Fila vazia (4)\n");
  exibirLog(f);
  prioritario = removerElemento(f);
  if (prioritario) printf("Prioritario: %i, %f\n", prioritario->id, prioritario->prioridade);
  else printf("Fila vazia (5)\n");
  exibirLog(f);
  prioritario = removerElemento(f);
  if (prioritario) printf("Prioritario: %i, %f\n", prioritario->id, prioritario->prioridade);
  else printf("Fila vazia (6)\n");
  exibirLog(f);
  prioritario = removerElemento(f);
  if (prioritario) printf("Prioritario: %i, %f\n", prioritario->id, prioritario->prioridade);
  else printf("Fila vazia (7)\n");
  exibirLog(f);

  printf("\n\n--- INSERÇÃO\n");
  if(inserirElemento(f, 1, 1)) printf("ok\n");
  else printf("nok (10)\n");
  exibirLog(f);
  if(inserirElemento(f, 3, 3)) printf("ok\n");
  else printf("nok (11)\n");
  exibirLog(f);
  if(inserirElemento(f, 2, 2)) printf("ok\n");
  else printf("nok (12)\n");
  exibirLog(f);
  if(inserirElemento(f, 0, 0.5)) printf("ok\n");
  else printf("nok (13)\n");
  exibirLog(f);
  if(inserirElemento(f, 5, 5)) printf("ok\n");
  else printf("nok (14)\n");
  exibirLog(f);
  
  printf("--- CONSULTA PRIORIDADE\n");
  exibirLog(f);
  if(consultarPrioridade(f, 1, &var1)) printf("ok - prioridade id %i eh %f\n", 1, var1);
  else printf("nok\n");
  if(consultarPrioridade(f, 3, &var2)) printf("ok - prioridade id %i eh %f\n", 3, var2);
  else printf("nok\n");
  if(consultarPrioridade(f, 2, &var3)) printf("ok - prioridade id %i eh %f\n", 2, var3);
  else printf("nok\n");
  if(consultarPrioridade(f, 0, &var4)) printf("ok - prioridade id %i eh %f\n", 0, var4);
  else printf("nok\n");
  
  printf("\n\n--- REDUZIR PRIORIDADE\n");
  if(reduzirPrioridade(f, 5, 0)) printf("ok\n");
  else printf("nok (15)\n");
  exibirLog(f);
  if(reduzirPrioridade(f, 0, 1)) printf("ok\n");
  else printf("nok (16) - esperado, nova prioridade eh maior\n");
  exibirLog(f);
  if(reduzirPrioridade(f, 3, 2)) printf("ok\n");
  else printf("nok (17)\n");
  exibirLog(f);
  if(reduzirPrioridade(f, 3, 1.5)) printf("ok\n");
  else printf("nok (18)\n");
  exibirLog(f);
  if(reduzirPrioridade(f, 4, 1)) printf("ok\n");
  else printf("nok (19) - esperado, elemento com id=4 nao existe\n");
  exibirLog(f);
  
  printf("--- CONSULTA PRIORIDADE\n");
  exibirLog(f);
  if(consultarPrioridade(f, 1, &var1)) printf("ok - prioridade id %i eh %f\n", 1, var1);
  else printf("nok\n");
  if(consultarPrioridade(f, 3, &var2)) printf("ok - prioridade id %i eh %f\n", 3, var2);
  else printf("nok\n");
  if(consultarPrioridade(f, 2, &var3)) printf("ok - prioridade id %i eh %f\n", 2, var3);
  else printf("nok\n");
  if(consultarPrioridade(f, 0, &var4)) printf("ok - prioridade id %i eh %f\n", 0, var4);
  else printf("nok\n");

  return 0;
}