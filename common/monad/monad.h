typedef struct {
  void *value;
} Maybe;

Maybe createMonad(void *pointer);
Maybe nothingMonad();
int isSomeMonad(Maybe maybe);
int isNothingMonad(Maybe maybe);
Maybe mapMonad(Maybe maybe, void *(*mapper)(void *));
Maybe flatMapMonad(Maybe maybe, Maybe (*mapper)(void *));
