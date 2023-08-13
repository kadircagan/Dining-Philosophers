Compile etmek için
$gcc -o hw2 hw2.c şeklinde derleyebilirsiniz
$./hw2 N 
$./hw2 <Filozof sayısı>

Kodda öncelikle her filozofumuza ayranı dağıtıyoruz bunu goGetAyran() metodunun içinde yapıyoruz her filozofun kendi döngüsünde en başta bunu yapıyoruz bu koşulu geçen filozoflar masada yerini alıyor. Eğer sağında ve solunda oturan kişi "EATİNG" statesinde değilse filozofumuz yemek yiyor ve bunu kaydediyoruz. Ayran bittiğinde halihazırda ayranını alan filozoflar varsa onlar da yemeklerini yiyene kadar loopdan çıkarmıyoruz. En sonunda onlar da yedisi taktirde loopu sonlandırıyoruz ve tur sonunda k değeri tekrar randomize edilip bir tur daha başlatılıyor. Ödevi yaparken temelini geeksforgeeksten aldım. Ayran sırasına semafor olduğu için sırayla almak zorunda kalıyorlar. Her turun sonunda ayran degeri kadar yemek yenmiş oluyor. Bunu semafor kullanarak garantiledim. 