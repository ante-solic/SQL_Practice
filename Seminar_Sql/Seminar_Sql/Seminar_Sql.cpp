#include <iostream>
#include <string>
#include <string.h>
#include <vector>

using namespace std;

string provjera;//globalni string jer nam na njega ne smiju utjecati petlje

void unos(vector<string>& leftSide, vector<string>& rightSide)
{
	int count = 0;
	string left, right;

	while (count < 5)
	{
		cout << "Left side element(s): ";
		cin >> left;
		leftSide.push_back(left);

		cout << "Right side element(s): ";
		cin >> right;
		rightSide.push_back(right);

		count++;
	}

	cout << endl;
}

void refleksivnost(string lijevi,string& desni)
{
	desni += lijevi; //dodajemo na desni string lijevu stranu, to jest prosirujemo je
}

void tranzitivnost(string& lijevi,string& desni,int a, vector<string> leftSide, vector<string> rightSide,string relacija)
{
	for (int i = 0; i < leftSide.size();i++)
	{
		string temp;
		string temp2;
		temp = leftSide[i];
		
		if (i == a)//da ne provjeravamo isti lijevi i desni string ako smo njih poslali u funkciju preskacemo ih
			continue;

		for (int j = 0; j < temp.size(); j++)//provjerava slovo po slovo element lijevog vektora nalazi li se u desnom stringu
		{
			if (desni.find(temp[j]) == string::npos)//u slucaju da se ne nalazi izlazi iz petlje i brise ako je ista spremljeno u string temp2 koji se nadodaju na desni string
			{
				temp2.clear();
				break;
			}
			else
				temp2 = rightSide[i];
		}

		for (int j = 0; j < temp2.size(); j++)//provjerava slovo po slovo element desnog vektora nalazi li se u desnom stringu
		{
			if (desni.find(temp2[j]) != string::npos)//u slucaju da se nalazi izlazi iz petlje jer ne dodajemo dva puta isto slovo na desnu stranu
			{
				temp2.clear();
				break;
			}
		}
		desni = desni + temp2;
	}

	if (desni.size()<relacija.size() && provjera!=desni) //ako nam se nakon rekurzije vrati isti string idemo na dodavanje slova iz relacije u else-u i ovo radimo dok ne postignemo relaciju u desnom stringu
	{
		provjera = desni; 
		tranzitivnost(lijevi, desni, 0, leftSide, rightSide, relacija);
	}
	else
	{
		for (int k = 0; k < relacija.size(); k++)
		{
			if (lijevi.find(relacija[k]) == string::npos && desni.find(relacija[k]) == string::npos)
			{
				lijevi += relacija[k];
				desni += relacija[k];
				tranzitivnost(lijevi, desni, 0, leftSide, rightSide, relacija);
			}
		}
	}
}

void minimalni(vector<string>& finalLeft, vector<string>& finalRight)//pronalazimo najkrace moguce kombinacije
{
	int min_size=finalLeft[0].size();//uzimamo da je najkraca moguca duljina duljina prvog elementa lijevog stringa

	for (int i = 1; i < finalLeft.size(); i++)
	{
		if (min_size > finalLeft[i].size())//u slucaju da nam je neki od sljedecih elemenata kraci njega uzimamo za najkraceg
			min_size = finalLeft[i].size();
	}

	vector<string>tempLeft = finalLeft;//lijevi i desni vektor spremamo u privremene vektore
	vector<string>tempRight = finalRight;

	finalLeft.clear();//praznimo vektore da ih mozemo popuniti samo sa najkracima
	finalRight.clear();

	for (int j = 0; j < tempLeft.size(); j++)
	{
		if (tempLeft[j].size() == min_size)//u slucaju u da se u privremenom stringu na nekoj poziciji nalazi element iste duljine kao i najmanja duljina spremamo je u finalni vektor
		{
			finalLeft.push_back(tempLeft[j]);
			finalRight.push_back(tempRight[j]);
		}
	}
}

void ispis(vector<string>& finalLeft, vector<string>& finalRight)
{
	for (int i = 0; i < finalLeft.size(); i++)
	{
		cout << finalLeft[i] << "->" << finalRight[i] << endl;
	}
}

int main()
{
	string left, right;
	vector<string> leftSide;
	vector<string> rightSide;

	vector<string> finalLeft;
	vector<string> finalRight;

	unos(leftSide, rightSide);

	// leftSide  = [DI, AJ, GB, AJ, I]
	// rightSide = [B, F, FJE, HD, CG]

	string relacija = "ABCDEFGHIJ";
	string lijevi;
	string desni;

	for (int i = 0; i < leftSide.size(); i++)
	{
		lijevi = leftSide[i];
		desni = rightSide[i];

		refleksivnost(lijevi, desni);
		
		tranzitivnost(lijevi, desni, i, leftSide, rightSide, relacija);

		cout << lijevi << "->" << desni << endl;

		finalLeft.push_back(lijevi);
		finalRight.push_back(desni);
	}

	minimalni(finalLeft, finalRight);

	cout << endl << "Najkraci moguci: " << endl;

	ispis(finalLeft, finalRight);
}