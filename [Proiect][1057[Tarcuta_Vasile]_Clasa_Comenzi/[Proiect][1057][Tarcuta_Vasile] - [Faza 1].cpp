#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

using namespace std;

class ExceptieInput {
	string mesaj;
public:
	ExceptieInput(string mesaj) : mesaj(mesaj) {

	};

	string getMesaj() {
		return this->mesaj;
	}
};

class MateriePrima {

	char* numeMateriePrima = nullptr;
	float cantitate = 0;

public:
	MateriePrima(char* numeMateriePrima, float cantitate) {
		if (numeMateriePrima != nullptr && strlen(numeMateriePrima) > 2) {
			this->numeMateriePrima = new char[strlen(numeMateriePrima) + 1];
			strcpy(this->numeMateriePrima, numeMateriePrima);
		}
		else this->numeMateriePrima = nullptr;

		this->cantitate = cantitate;
	}

	MateriePrima() {

	};

	MateriePrima(float cantitate) {
		this->cantitate = cantitate;
	}

	float addCantitate(float cantitate) {
		this->cantitate += cantitate;
		return this->cantitate;
	}

	float substractCantitate(float cantitate) {
		this->cantitate -= cantitate;
		return this->cantitate;
	}

	MateriePrima& operator++() {
		this->cantitate++;
		return *this;
	}

	MateriePrima operator++(int) {
		MateriePrima copie = *this;
		this->cantitate++;
		return copie;
	}



	MateriePrima(const MateriePrima& mp) {
		if (strlen(mp.numeMateriePrima) > 2 && mp.numeMateriePrima != nullptr) {
			this->numeMateriePrima = new char[strlen(mp.numeMateriePrima) + 1];
			strcpy(this->numeMateriePrima, mp.numeMateriePrima);
		}
		this->cantitate = mp.cantitate;
	}

	void setNumeMateriePrima(char* numeMateriePrima) {
		if (numeMateriePrima != nullptr && strlen(numeMateriePrima) > 2) {
			this->numeMateriePrima = new char[strlen(numeMateriePrima) + 1];
			strcpy(this->numeMateriePrima, numeMateriePrima);
		}
	}

	char* getNumeMateriePrima() {
		return this->numeMateriePrima;
	}

	void setCantitate(float cantitate) {
		if (cantitate > 0)
			this->cantitate = cantitate;
		else throw new ExceptieInput("Cantitatea este negativa!!");
	}

	float getCantitate() {
		return this->cantitate;
	}


	friend bool operator==(MateriePrima& mp1, MateriePrima& mp2) {
		return (mp1.getNumeMateriePrima() == mp2.getNumeMateriePrima()) &&
			(mp1.getCantitate() == mp2.getCantitate());
	}

	MateriePrima& operator=(const MateriePrima& mp) {
		if (this != &mp) {
			delete[] this->numeMateriePrima;
			this->numeMateriePrima = nullptr;
			if (strlen(mp.numeMateriePrima) > 2 && mp.numeMateriePrima != nullptr) {
				this->numeMateriePrima = new char[strlen(mp.numeMateriePrima) + 1];
				strcpy(this->numeMateriePrima, mp.numeMateriePrima);
			}
			this->cantitate = mp.cantitate;
		}
		return *this;
	}


	bool areStocSuficient(int cantitate) const {
		return  this->cantitate >= cantitate;
	}

	void scaziStoc(int cantitate) {
		this->cantitate -= cantitate;
	}

	friend ostream& operator<<(ostream& out, const MateriePrima& mp) {
		out << "\n\n\n=====================<<Out<<=======================";
		out << "\nDenumire materie prima: ";
		if (mp.numeMateriePrima != nullptr)
			out << mp.numeMateriePrima;
		else out << "-";
		out << "\nCantitate din materie prima: ";
		out << mp.cantitate;
		out << "\n=====================<<Out<<=======================";
		return out;
	}

	friend istream& operator>>(istream& in, MateriePrima& mp) {
		delete[] mp.numeMateriePrima;
		mp.numeMateriePrima = nullptr;
		cout << "\n====================>>>In>>>=======================";
		cout << "\nIntroduceti numele materiei prime: ";
		getchar();
		string buffer;
		getline(in, buffer);
		mp.numeMateriePrima = new char[buffer.length() + 1];
		strcpy(mp.numeMateriePrima, buffer.data());
		cout << "\nIntroduceti cantitatea: ";
		in >> mp.cantitate;
		cout << "\n====================>>>In>>>=======================";
		return in;
	}
	//operator +
	MateriePrima operator+(int stocSuplimentar) {
		if (stocSuplimentar > 0) {
			MateriePrima rez = *this;
			rez.cantitate += stocSuplimentar;
			return rez;
		}
	}

	bool operator!() {
		return !this->cantitate;
	}

	~MateriePrima() {

		delete[] this->numeMateriePrima;
		this->numeMateriePrima = nullptr;
	}
};

MateriePrima operator+(int stocSuplimentar, MateriePrima mp) {
	return mp + stocSuplimentar;
}

class Reteta {
	int timpDePreparare = 0;
	int nrIngrediente = 0;
	MateriePrima* ingrediente = nullptr;
	float* gramajIngrediente = nullptr;
	int nrPortii = 0;

public:

	Reteta(int timpDePreparare, int nrIngrediente, MateriePrima* ingrediente, float* gramajIngrediente, int nrPortii) {
		this->timpDePreparare = timpDePreparare;
		if (nrIngrediente > 0 && ingrediente != nullptr) {
			this->nrIngrediente = nrIngrediente;
			this->ingrediente = new MateriePrima[this->nrIngrediente];
			for (int i = 0;i < this->nrIngrediente;i++)
				this->ingrediente[i] = ingrediente[i];
		}

		if (nrIngrediente > 0 && gramajIngrediente != nullptr) {
			this->nrIngrediente = nrIngrediente;
			this->gramajIngrediente = new float[this->nrIngrediente];
			for (int i = 0;i < this->nrIngrediente;i++)
				this->gramajIngrediente[i] = gramajIngrediente[i];
		}

		this->nrPortii = nrPortii;

	}

	Reteta() {};

	void setTimpDePreparare(int timpDePreparare) {
		this->timpDePreparare = timpDePreparare;
	}

	int getTimpDePreparare() {
		return this->timpDePreparare;
	}

	void setIngrediente(int nrIngrediente, MateriePrima* ingrediente) {
		if (nrIngrediente > 0 && ingrediente != nullptr) {
			this->nrIngrediente = nrIngrediente;
			this->ingrediente = new MateriePrima[this->nrIngrediente];
			for (int i = 0;i < this->nrIngrediente;i++)
				this->ingrediente[i] = ingrediente[i];
		}
		else throw new ExceptieInput("Nr de ingrediente este mai mic sau egal cu 0 sau nu exista vectorul de ingrediente!");
	}

	MateriePrima* getIngrediente() {
		return this->ingrediente;
	}

	void setGramaje(int nrIngrediente, float* gramajIngrediente) {
		if (nrIngrediente > 0 && gramajIngrediente != nullptr) {
			this->nrIngrediente = nrIngrediente;
			this->gramajIngrediente = new float[this->nrIngrediente];
			for (int i = 0;i < this->nrIngrediente;i++)
				this->gramajIngrediente[i] = gramajIngrediente[i];
		}
	}

	float* getGramajIngrediente() {
		return this->gramajIngrediente;

	}


	void setNrPortii(int nrPortii) {
		this->nrPortii = nrPortii;
	}

	int getNrPortii() {
		return this->nrPortii;
	}

	bool operator==(const Reteta& r) {
		if (this->timpDePreparare == r.timpDePreparare && this->nrIngrediente == r.nrIngrediente && this->nrPortii == r.nrPortii) {
			for (int i = 0; i < this->nrIngrediente; ++i) {
				// Verifica fiecare ingredient si gramaj
				if (!(this->ingrediente[i] == r.ingrediente[i] && this->gramajIngrediente[i] == r.gramajIngrediente[i])) {
					return false;
				}
			}
			return true;
		}
		return false;
	}


	Reteta(int timpDePreparare, int nrPortii) {
		this->timpDePreparare = timpDePreparare;
		this->nrPortii = nrPortii;
	}

	Reteta(const Reteta& r) {
		this->timpDePreparare = r.timpDePreparare;
		if (r.nrIngrediente > 0 && r.ingrediente != nullptr) {
			this->nrIngrediente = r.nrIngrediente;
			this->ingrediente = new MateriePrima[this->nrIngrediente];
			for (int i = 0;i < this->nrIngrediente;i++)
				this->ingrediente[i] = r.ingrediente[i];
		}

		if (r.nrIngrediente > 0 && r.gramajIngrediente != nullptr) {
			this->nrIngrediente = r.nrIngrediente;
			this->gramajIngrediente = new float[this->nrIngrediente];
			for (int i = 0;i < this->nrIngrediente;i++)
				this->gramajIngrediente[i] = r.gramajIngrediente[i];
		}

		this->nrPortii = r.nrPortii;

	}

	Reteta& operator=(const Reteta& r) {
		if (this != &r) {
			delete[] this->gramajIngrediente;
			this->gramajIngrediente = nullptr;
			delete[] this->ingrediente;
			this->ingrediente = nullptr;
			this->timpDePreparare = r.timpDePreparare;
			if (r.nrIngrediente > 0 && r.ingrediente != nullptr) {
				this->nrIngrediente = r.nrIngrediente;
				this->ingrediente = new MateriePrima[this->nrIngrediente];
				for (int i = 0;i < this->nrIngrediente;i++)
					this->ingrediente[i] = r.ingrediente[i];
			}

			if (r.nrIngrediente > 0 && r.gramajIngrediente != nullptr) {
				this->nrIngrediente = r.nrIngrediente;
				this->gramajIngrediente = new float[this->nrIngrediente];
				for (int i = 0;i < this->nrIngrediente;i++)
					this->gramajIngrediente[i] = r.gramajIngrediente[i];
			}

			this->nrPortii = r.nrPortii;
		}
		return *this;
	}

	friend ostream& operator<<(ostream& out, Reteta& r) {
		out << "\n==============<<OUT<<==================";
		out << "\nTimp de Preparare: ";
		out << r.timpDePreparare;
		out << "\nNumar ingrediente: ";
		out << r.nrIngrediente;
		out << "\nIngrediente: ";
		if (r.nrIngrediente > 0 && r.ingrediente != nullptr) {
			for (int i = 0;i < r.nrIngrediente;i++)
				out << r.ingrediente[i] << " ";
		}
		else out << "-";
		out << "\nGramaj inngrediente: ";
		if (r.nrIngrediente > 0 && r.gramajIngrediente != nullptr) {
			for (int i = 0;i < r.nrIngrediente;i++)
				out << r.gramajIngrediente[i] << " ";
		}
		else out << "-";
		out << "\nNumar portii: ";
		out << r.nrPortii;
		out << "\n==============<<OUT<<==================";
		return out;
	}

	friend istream& operator>>(istream& in, Reteta& r) {
		cout << "\n==================>>IN>>==============";
		cout << "\nIntroduceti timp de preparare: ";
		in >> r.timpDePreparare;
		cout << "\nNr ingrediente: ";
		in >> r.nrIngrediente;
		cout << "\nIntroduceti ingredientele: ";
		r.ingrediente = new MateriePrima[r.nrIngrediente];
		for (int i = 0;i < r.nrIngrediente;i++)
		{
			cout << "\n   Ingredientul " << i << ": ";
			in >> r.ingrediente[i];

		}
		cout << "\nIntroduceti gramajele fiecarui ingredient: ";
		r.gramajIngrediente = new float[r.nrIngrediente];
		for (int i = 0;i < r.nrIngrediente;i++) {
			cout << "\n      Gramaj ingredient " << i << ": ";
			in >> r.gramajIngrediente[i];
		}
		cout << "\nIntroduceti numarul de portii: ";
		in >> r.nrPortii;
		cout << "\n====================>>IN>>==============";
		return in;
	}

	~Reteta() {
		delete[] this->gramajIngrediente;
		this->gramajIngrediente = nullptr;
		delete[] this->ingrediente;
		this->ingrediente = nullptr;
	}
};

class Preparat {
	char* denumirePreparat = nullptr;
	int pretPerPortie = 0;
	Reteta retetaPreparat;

public:

	Preparat() {

	}

	Preparat(char* denumirePreparat, int pretPerPortie, Reteta retetaPreparat) {
		if (strlen(denumirePreparat) > 2 && denumirePreparat != nullptr) {
			this->denumirePreparat = new char[strlen(denumirePreparat) + 1];
			strcpy(this->denumirePreparat, denumirePreparat);
		}
		else this->denumirePreparat = nullptr;
		this->pretPerPortie = pretPerPortie;
		this->retetaPreparat = retetaPreparat;
	}

	Preparat(const Preparat& p) {
		if (strlen(p.denumirePreparat) >= 2 && p.denumirePreparat != nullptr) {
			this->denumirePreparat = new char[strlen(denumirePreparat)];
			strcpy(this->denumirePreparat, p.denumirePreparat);
		}
		this->pretPerPortie = p.pretPerPortie;
		this->retetaPreparat = p.retetaPreparat;
	}

	Preparat& operator=(const Preparat& p) {
		if (this != &p) {
			delete[] this->denumirePreparat;
			this->denumirePreparat = nullptr;
			if (p.denumirePreparat != nullptr && strlen(p.denumirePreparat) >= 2) {
				this->denumirePreparat = new char[strlen(p.denumirePreparat) + 1];
				strcpy(this->denumirePreparat, p.denumirePreparat);
			}
			this->pretPerPortie = p.pretPerPortie;
			this->retetaPreparat = p.retetaPreparat;
		}
		return *this;
	}

	void setDenumirePreparat(char* denumirePreparat) {
		if (denumirePreparat != nullptr && strlen(denumirePreparat) >= 2)
			this->denumirePreparat = denumirePreparat;
		else throw new ExceptieInput("Numele nu este destul de lung!");
	}

	char* getDenumirePreparat() {
		return this->denumirePreparat;
	}

	void setPretPerPortie(int pretPerPortie) {
		if (pretPerPortie >= 0)
			this->pretPerPortie = pretPerPortie;
		else throw new ExceptieInput("Pretul nu poate fi negativ!");
	}

	float getPretPerPortie() const {
		return this->pretPerPortie;
	}


	friend ostream& operator<<(ostream& out, Preparat& p) {
		out << "\n===========<<Preparat<<================";
		out << "\nDenumirea preparatului: ";
		out << p.denumirePreparat;
		out << "\nPret per portie: ";
		out << p.pretPerPortie;
		out << "\nReteta preparat: ";
		out << p.retetaPreparat;
		return out;
	}

	friend istream& operator>>(istream& in, Preparat& p) {
		cout << "\n=====================>>Preparat>>===========";
		cout << "\nIntroduceti denumirea preparatului: ";
		in >> p.denumirePreparat;
		getchar();
		string buffer;
		getline(in, buffer);
		p.denumirePreparat = new char[buffer.length() + 1];
		strcpy(p.denumirePreparat, buffer.data());
		cout << "\nIntroduceti pretul per portie: ";
		in >> p.pretPerPortie;
		cout << "\nIntroduceti reteta preparatului: ";
		in >> p.retetaPreparat;
		cout << "\n=====================>>Preparat>>===========";
		return in;
	}

	bool areMateriiPrimeSuficiente(const MateriePrima& materiePrima, float cantitate) {
		return materiePrima.areStocSuficient(cantitate);
	}

	float pretTotalComanda(int nrPortiiComandate) {
		return this->pretPerPortie * nrPortiiComandate;
	}

	void afisarePret() {
		cout << "Pretul este de: " << this->pretPerPortie << " lei.";
	}

	~Preparat() {
		delete[] this->denumirePreparat;
		this->denumirePreparat = nullptr;
	}
};

class Comanda {
	const int nrComanda = 0;
	int nrPreparate = 0;
	Preparat* preparateComandate = nullptr;
	int* preturiPreparate = nullptr;

public:


	Comanda(int nrComanda = 0, int nrPreparate = 0, Preparat* preparateComandate = nullptr, int* preturiPreparate = nullptr) : nrComanda(nrComanda) {
		this->nrPreparate = nrPreparate;
		if (nrPreparate > 0 && preparateComandate != nullptr)
		{
			this->preparateComandate = new Preparat[nrPreparate];
			for (int i = 0;i < this->nrPreparate;i++)
				this->preparateComandate[i] = preparateComandate[i];
		}
		if (nrPreparate > 0 && preturiPreparate != nullptr)
		{
			this->preturiPreparate = new int[nrPreparate];
			for (int i = 0;i < this->nrPreparate;i++)
				this->preturiPreparate[i] = preturiPreparate[i];
		}
	}

	Comanda(int nrComanda) : nrComanda(nrComanda) {};

	Comanda(const Comanda& c) : nrComanda(c.nrComanda) {
		this->nrPreparate = c.nrPreparate;
		if (c.nrPreparate > 0 && c.preparateComandate != nullptr)
		{
			this->preparateComandate = new Preparat[c.nrPreparate];
			for (int i = 0;i < this->nrPreparate;i++)
				this->preparateComandate[i] = c.preparateComandate[i];
		}
		if (c.nrPreparate > 0 && c.preturiPreparate != nullptr)
		{
			this->preturiPreparate = new int[c.nrPreparate];
			for (int i = 0;i < this->nrPreparate;i++)
				this->preturiPreparate[i] = c.preturiPreparate[i];
		}
	}
	//returneaza pretul unui produs de pe o pozitie data
	int operator[](int pozitie) {
		if (pozitie >= 0 && pozitie < this->nrPreparate) {
			if (this->preturiPreparate != nullptr) {
				return this->preturiPreparate[pozitie];
			}
		}
		return 0;
	}

	void setNrPreparate(int nrPreparate) {
		this->nrPreparate = nrPreparate;
	}

	int getNrPreparate() {
		return this->nrPreparate;
	}

	void setPreparateComandate(int nrPreparate, Preparat* preparateComandate) {
		this->nrPreparate = nrPreparate;
		if (nrPreparate > 0 && preparateComandate != nullptr)
		{
			this->preparateComandate = new Preparat[nrPreparate];
			for (int i = 0;i < this->nrPreparate;i++)
			{
				cout << "\nPreparatul nr " << i + 1 << ":";
				cin >> this->preparateComandate[i];
			}
		}
		else throw new ExceptieInput("Nr de preparate este mai mic sau egal cu 0 sau nu exista vectorul de preparate!");
	}

	Preparat* getPreparateComandate() {
		return this->preparateComandate;
	}

	void setPretPreparate(int nrPreparate, Preparat* preturiPreparate) {
		this->nrPreparate = nrPreparate;
		if (nrPreparate > 0 && preturiPreparate != nullptr)
		{
			this->preturiPreparate = new int[nrPreparate];
			for (int i = 0;i < this->nrPreparate;i++)
			{
				cout << "\nPreparatul nr " << i + 1 << ":";
				cin >> this->preturiPreparate[i];
			}
		}
		else throw new ExceptieInput("Nr de preparate este mai mic sau egal cu 0 sau nu exista vectorul de preturi!");
	}

	void nota_de_plata() {
		float total = 0;

		cout << "\n============================================";
		cout << "\n               Nota de plata";
		cout << "\n============================================";

		if (this->nrPreparate > 0 && this->preparateComandate != nullptr && this->preturiPreparate != nullptr) {
			for (int i = 0; i < this->nrPreparate; ++i) {
				cout << "\n" << this->preparateComandate[i].getDenumirePreparat() << " - " << this->preturiPreparate[i] << " lei";
				total += this->preturiPreparate[i];
			}
		}
		else {
			cout << "\nComanda nu contine preparate.";
		}

		cout << "\n--------------------------------------------";
		cout << "\nTOTAL: " << total << " lei";
		cout << "\n============================================\n";
	}

	int* getPretPreparate() {
		return this->preturiPreparate;
	}

	Comanda& operator=(const Comanda& c) {
		if (this != &c) {
			delete[] this->preparateComandate;
			this->preparateComandate = nullptr;
			delete[] this->preturiPreparate;
			this->preturiPreparate = nullptr;
			this->nrPreparate = c.nrPreparate;
			if (c.nrPreparate > 0 && c.preparateComandate != nullptr)
			{
				this->preparateComandate = new Preparat[c.nrPreparate];
				for (int i = 0;i < this->nrPreparate;i++)
					this->preparateComandate[i] = c.preparateComandate[i];
			}
			if (c.nrPreparate > 0 && c.preturiPreparate != nullptr)
			{
				this->preturiPreparate = new int[c.nrPreparate];
				for (int i = 0;i < this->nrPreparate;i++)
					this->preturiPreparate[i] = c.preturiPreparate[i];
			}
		}
		return *this;
	}

	friend ostream& operator<<(ostream& out, const Comanda& c) {
		out << "\n\n\n++++++++++++++++++<<Comanda<<++++++++++++++++++";
		out << "\n   Id comanda: ";
		out << c.nrComanda;
		out << "\n  Nr Preparate: ";
		out << c.nrPreparate;
		out << "\n  Preparate comandate: ";
		if (c.nrPreparate > 0 && c.preparateComandate != nullptr)
			for (int i = 0;i < c.nrPreparate;i++)
				out << c.preparateComandate[i] << " ";
		else out << "-";
		out << "\n  Preturi preparate comandate: ";
		if (c.nrPreparate > 0 && c.preturiPreparate != nullptr)
			for (int i = 0;i < c.nrPreparate;i++)
				out << c.preturiPreparate[i] << " ";
		else out << "-";
		out << "\n++++++++++++++++++<<Comanda<<++++++++++++++++++";
		return out;
	}

	friend istream& operator>>(istream& in, Comanda& c) {
		cout << "\n\n\n++++++++++++++++++<<Comanda<<++++++++++++++++++";
		cout << "\n  Nr Preparate: ";
		in >> c.nrPreparate;
		cout << "\n  Preparate comandate: ";
		if (c.nrPreparate > 0) {
			c.preparateComandate = new Preparat[c.nrPreparate];
			for (int i = 0;i < c.nrPreparate;i++)
			{
				cout << "\nPreparatul nr " << i + 1 << ":";
				in >> c.preparateComandate[i];
			}
		}

		cout << "\n  Preturi preparate comandate: ";
		if (c.nrPreparate > 0) {
			c.preturiPreparate = new int[c.nrPreparate];
			for (int i = 0;i < c.nrPreparate;i++) {
				cout << "\nPret preparat " << i + 1 << ": ";
				in >> c.preturiPreparate[i];
			}
		}
		cout << "\n++++++++++++++++++<<Comanda<<++++++++++++++++++";
		return in;
	}



	void adaugaPreparat(const Preparat& preparat, int cantitate) {
		/*if (cantitate >= preparat.getCantitate())
		{*/
		Preparat* noiPreparate = new Preparat[nrPreparate + 1];
		int* noiPreturi = new int[nrPreparate + 1];

		for (int i = 0; i < nrPreparate; ++i) {
			noiPreparate[i] = preparateComandate[i];
			noiPreturi[i] = preturiPreparate[i];
		}

		noiPreparate[nrPreparate] = preparat;
		noiPreturi[nrPreparate] = cantitate * preparat.getPretPerPortie();

		nrPreparate++;

		delete[] preparateComandate;
		delete[] preturiPreparate;

		preparateComandate = noiPreparate;
		preturiPreparate = noiPreturi;
		/*}
		else throw ExceptieInput("Nu mai avem ingredientele necesare!");*/
	}

	~Comanda() {
		delete[] this->preparateComandate;
		this->preparateComandate = nullptr;
		delete[] this->preturiPreparate;
		this->preturiPreparate = nullptr;
	}
};

class Masa {
	static float procentBacsisMinim;
	static int lungimeCodMasa;
	char* codMasa = nullptr;
	Comanda comanda;
public:

	Masa() : codMasa(nullptr), comanda() {}

	Masa(char* codMasa, Comanda comanda) {
		if (codMasa != nullptr && strlen(codMasa) == lungimeCodMasa) {
			this->codMasa = new char[lungimeCodMasa + 1];
			strcpy(this->codMasa, codMasa);
		}
		else this->codMasa = nullptr;
		this->comanda = comanda;
	}

	Masa(const Masa& m) {
		if (m.codMasa != nullptr && strlen(m.codMasa) == m.lungimeCodMasa) {
			this->codMasa = new char[m.lungimeCodMasa + 1];
			strcpy(this->codMasa, m.codMasa);
		}
		else this->codMasa = nullptr;
		this->comanda = m.comanda;

	}

	Masa operator=(const Masa& m) {
		if (this != &m) {
			delete[] this->codMasa;
			this->codMasa = nullptr;
			if (m.codMasa != nullptr && strlen(m.codMasa) == m.lungimeCodMasa) {
				this->codMasa = new char[m.lungimeCodMasa + 1];
				strcpy(this->codMasa, m.codMasa);
			}
			else this->codMasa = nullptr;
			this->comanda = m.comanda;
		}

		return *this;
	}

	friend ostream& operator<<(ostream& out, const Masa& masa) {
		out << "\n==============<<MASA<<===============";
		out << "Cod Masa: ";
		if (masa.codMasa != nullptr) {
			out << masa.codMasa;
		}
		else {
			out << "-";
		}
		out << "\nComanda: " << masa.comanda;
		out << "\n==============<<MASA<<===============";
		return out;

	}

	friend istream& operator>>(istream& in, Masa& masa) {
		cout << "\n==============>>MASA>>===============";
		cout << "\nIntroduceti codul mesei: ";
		char buffer[100];
		in >> buffer;
		if (masa.codMasa != nullptr) {
			delete[] masa.codMasa;
		}
		masa.codMasa = new char[strlen(buffer) + 1];
		strcpy(masa.codMasa, buffer);
		cout << "\nIntroduceti comanda asociata mesei: ";
		in >> masa.comanda;
		return in;
	}


	~Masa() {
		delete[] this->codMasa;
		this->codMasa = nullptr;
	}
};

float Masa::procentBacsisMinim = 0.1;
int Masa::lungimeCodMasa = 5;

int main()
{
	char rosii[] = "rosii";
	char ardei[] = "ardei";
	char pui[] = "pui";
	char cartofi[] = "cartofi";
	char oua[] = "oua";
	char vinete[] = "vinete";
	char porc[] = "porc";
	char faina[] = "faina";
	char zahar[] = "zahar";
	char sare[] = "sare";
	char piper[] = "piper";
	char drojdieUscata[] = "drojdie uscata";
	char uleiDeMasline[] = "ulei de masline";
	char sosRosii[] = "sos de rosii";
	char mozzarella[] = "mozzarella";
	char parmezan[] = "parmezan";
	char spaghetti[] = "spaghetti";
	char guanciale[] = "guanciale";
	char ciuperci[] = "ciuperci";
	char bacon[] = "bacon";
	char ouaGaina[] = "oua de gaina";
	char lapte[] = "lapte";
	char unt[] = "unt";
	char ceapa[] = "ceapa";
	char usturoi[] = "usturoi";
	char carneVita[] = "carne de vita";
	char branzaTelemea[] = "branza telemea";
	char aluat[] = "aluat";
	char scortisoara[] = "scortisoara";
	char ghimbir[] = "ghimbir";
	char mere[] = "mere";
	char iaurt[] = "iaurt";
	char curry[] = "curry";
	char coriandru[] = "coriandru";
	char salata[] = "salata";
	char crutoane[] = "crutoane";
	char sosCaesar[] = "sos Caesar";

	MateriePrima scortisoara1(scortisoara, 2), ghimbir1(ghimbir, 15), mere1(mere, 300), iaurt1(iaurt, 100), curry1(curry, 10), coriandru1(coriandru, 5);
	MateriePrima salata1(salata, 150), crutoane1(crutoane, 50), sosCaesar1(sosCaesar, 30);
	MateriePrima ciuperci1(ciuperci, 15), bacon1(bacon, 25), ouaGaina1(ouaGaina, 20), lapte1(lapte, 200), unt1(unt, 30);
	MateriePrima ceapa1(ceapa, 20), usturoi1(usturoi, 10), carneVita1(carneVita, 150), branzaTelemea1(branzaTelemea, 50), aluat1(aluat, 200);
	MateriePrima rosii1(rosii, 12), ardei1(ardei, 30), pui1(pui, 10), cartofi1(cartofi, 12), oua1(oua, 40), vinete1(vinete, 10), porc1(porc, 30), faina1(faina, 10), drojdieUscata1(drojdieUscata, 10);
	MateriePrima zahar1(zahar, 5), uleiDeMasline1(uleiDeMasline, 5), sare1(sare, 2), sosRosii1(sosRosii, 20), mozzarella1(mozzarella, 10), parmezan1(parmezan, 10);
	MateriePrima spaghetti1(spaghetti, 20), piper1(piper, 2), guanciale1(guanciale, 5);


	//Pizza Margherita
	MateriePrima ingredientePizzaMargherita[] = { faina1, uleiDeMasline1, sare1, sosRosii1, mozzarella1 };
	float gramajePizzaMargherita[] = { 250, 50, 10,  150, 200 };
	Reteta PizzaMargerita(30, 5, ingredientePizzaMargherita, gramajePizzaMargherita, 1);
	char pizzaMargherita[] = "Pizza Margherita";
	Preparat PizzaMargherita1(pizzaMargherita, 30, PizzaMargerita);
	cout << "\n\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
	cout << PizzaMargherita1;
	cout << "\n\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";

	//Paste Carbonara
	MateriePrima ingredientePasteCarbonara[] = { spaghetti1, oua1, sare1, parmezan1, guanciale1 };
	float gramajeCarbonara[] = { 1, 5, 5, 250, 100 };
	Reteta SpaghettiCarbonara(30, 5, ingredientePasteCarbonara, gramajeCarbonara, 1);
	char spaghettiCarbonara[] = "Spaghetti Carbonara";
	Preparat SpaghettiCarbonara1(spaghettiCarbonara, 45, SpaghettiCarbonara);
	cout << "\n\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
	cout << SpaghettiCarbonara1;
	cout << "\n\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";

	// Preparat omleta cu ciuperci
	MateriePrima ingredienteOmletaCiuperci[] = { oua1, ciuperci1, branzaTelemea1, sare1, piper1 };
	float gramajeOmletaCiuperci[] = { 4, 100, 50, 2, 2 };
	Reteta OmletaCiuperciRecipe(15, 5, ingredienteOmletaCiuperci, gramajeOmletaCiuperci, 1);
	char omletaCiuperci[] = "Omleta cu Ciuperci";
	Preparat OmletaCiuperci1(omletaCiuperci, 20, OmletaCiuperciRecipe);
	cout << "\n\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
	cout << OmletaCiuperci1;
	cout << "\n\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";

	// Pizza Quattro Formaggi
	MateriePrima ingredienteQuattroFormaggi[] = { aluat1, sosRosii1, mozzarella1, parmezan1, branzaTelemea1 };
	float gramajeQuattroFormaggi[] = { 300, 150, 200, 50, 50 };
	Reteta QuattroFormaggiRecipe(35, 5, ingredienteQuattroFormaggi, gramajeQuattroFormaggi, 1);
	char pizzaQuattroFormaggi[] = "Pizza Quattro Formaggi";
	Preparat QuattroFormaggi1(pizzaQuattroFormaggi, 40, QuattroFormaggiRecipe);
	cout << "\n\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
	cout << QuattroFormaggi1;
	cout << "\n\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";

	// Supa de ceapa
	MateriePrima ingredienteSupaCeapa[] = { ceapa1, unt1, sare1, piper1 };
	float gramajeSupaCeapa[] = { 200, 30, 5, 2 };
	Reteta SupaCeapaRecipe(30, 4, ingredienteSupaCeapa, gramajeSupaCeapa, 1);
	char supaCeapa[] = "Supa de Ceapa";
	Preparat SupaCeapa1(supaCeapa, 35, SupaCeapaRecipe);
	cout << "\n\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
	cout << SupaCeapa1;
	cout << "\n\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";

	// Placinta cu mere
	MateriePrima ingredientePlacintaMere[] = { aluat1, mere1, zahar1, scortisoara1, unt1 };
	float gramajePlacintaMere[] = { 250, 400, 100, 5, 30 };
	Reteta PlacintaMereRecipe(40, 5, ingredientePlacintaMere, gramajePlacintaMere, 1);
	char placintaMere[] = "Placinta cu Mere";
	Preparat PlacintaMere1(placintaMere, 50, PlacintaMereRecipe);
	cout << "\n\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
	cout << PlacintaMere1;
	cout << "\n\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";

	// Pui Tikka Masala
	MateriePrima ingredientePuiTikkaMasala[] = { pui1, rosii1, ceapa1, usturoi1, ghimbir1, iaurt1, curry1, coriandru1, sare1, piper1 };
	float gramajePuiTikkaMasala[] = { 300, 250, 150, 10, 10, 100, 20, 5, 3, 3 };
	Reteta PuiTikkaMasalaRecipe(45, 10, ingredientePuiTikkaMasala, gramajePuiTikkaMasala, 1);
	char puiTikkaMasala[] = "Pui Tikka Masala";
	Preparat PuiTikkaMasala1(puiTikkaMasala, 55, PuiTikkaMasalaRecipe);
	cout << "\n\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
	cout << PuiTikkaMasala1;
	cout << "\n\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";

	// Salata Caesar
	MateriePrima ingredienteSalataCaesar[] = { pui1, salata1, crutoane1, parmezan1, sosCaesar1 };
	float gramajeSalataCaesar[] = { 200, 150, 50, 30, 50 };
	Reteta SalataCaesarRecipe(20, 5, ingredienteSalataCaesar, gramajeSalataCaesar, 1);
	char salataCaesar[] = "Salata Caesar";
	Preparat SalataCaesar1(salataCaesar, 25, SalataCaesarRecipe);
	cout << "\n\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
	cout << SalataCaesar1;
	cout << "\n\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";

	int ok = -1;
	char codMasa[] = "2AB33";
	Comanda comanda;
	do {
		/*Masa m1;
		cin >> m1;*/
		string comandaTastatura;
		cout << "\n+=+=+=+=+=+=+=+=+= LEGENDA +=+=+=+=+=+=+=+=+=";
		cout << "\n   1. afisare_meniu -> afiseaza meniul de produse";
		cout << "\n   2. adauga_la_comanda -> adauga un alt produs la comanda";
		cout << "\n   3. nota_de_plata -> afiseaza nota de plata";

		cout << "\nIntroduceti comanda: ";
		getline(cin, comandaTastatura);
		if (comandaTastatura == "afisare_meniu") {
			cout << "\n\n=========PREPARATELE NOASTRE========";
			cout << "\n   1->Pizza Margherita";
			cout << "\n   2->Paste Carbonara";
			cout << "\n   3->Omleta cu ciuperci";
			cout << "\n   4->Pizza Quattro Formaggi";
			cout << "\n   5->Supa de ceapa";
			cout << "\n   6->Placinta cu mere";
			cout << "\n   7->Pui Tikka Masala";
			cout << "\n   8->Salata Caesar";
			cout << "\n   0->IESIRE";
			cout << "\n======================================";
		}
		if (comandaTastatura == "adauga_la_comanda")
		{

			cout << "\n\nAdaugati la comanda:\n\n";
			cin >> ok;

			switch (ok) {
			case 1:
				comanda.adaugaPreparat(PizzaMargherita1, 45);
				break;
			case 2:
				comanda.adaugaPreparat(SpaghettiCarbonara1, 43);
				break;
			case 3:
				comanda.adaugaPreparat(OmletaCiuperci1, 3);
				break;
			case 4:
				comanda.adaugaPreparat(QuattroFormaggi1, 1);
				break;
			case 5:
				comanda.adaugaPreparat(SupaCeapa1, 2);
				break;
			case 6:
				comanda.adaugaPreparat(PlacintaMere1, 1);
				break;
			case 7:
				comanda.adaugaPreparat(PuiTikkaMasala1, 2);
				break;
			case 8:
				comanda.adaugaPreparat(SalataCaesar1, 2);
				break;
			case 0:
				cout << "\nIesire...\n";
				break;
			}
		}
		if (comandaTastatura == "nota_de_plata") {
			comanda.nota_de_plata();
		}


	} while (ok != 0);


	return 0;
}
