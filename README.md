# Travel_Agency
Jest to program współpracujący z bazą danych (SQlite). W bazie danych przechowywane są informacje o wycieczkach natomiast informacje o biurach podróży pobierane są z pliku Json. 
Na podstawie tych informacji powstają oferty. Program pozwala użytkownikowi zobaczyć informacje tj. 
-biuro podróży które zorganizowało najwięcej wycieczek lub najwięcej zarobiło, 
-kraj do którego najczęściej podróżowano, 
-zobaczyć wycieczki tylko do europy(informacje o krajach zaliczających się występują w pliku txt). 

Dodatkowo program pozwala zobaczyć zestawienia:
-średnia cena wycieczek każdego biura podróży z wycieczką o cenie najbliższa do niej, 
-zestawienie krajów i dla każdego nazwa biura podróży które najczęściej organizowało do niego wycieczki.

Program zwraca też mapy: 
-mapę której kluczem jest ilość osób biorących udział w wycieczce a wartością kolekcja bez duplikatów wycieczek z taką ilością,
-mapę gdzie kluczem jest ilość osób a wartością najdroższa wycieczka o takiej ilości osób (mapa posortowana malejąco według kosztu wycieczki na jedną osobę)
