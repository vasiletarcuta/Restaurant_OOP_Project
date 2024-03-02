#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

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

class IFisiere
{
public:

	virtual void scrieFisierBinar(fstream& f) = 0;
	virtual void citesteFisierBinar(fstream& f) = 0;
	virtual void scrieFisierText(ofstream& out) = 0;
	virtual void citesteFisierText(ifstream& in) = 0;

};

class MateriePrima : IFisiere {

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
		out << "\nCantitate disponibila in stoc: ";
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

	void scrieFisierBinar(fstream& f) {
		int lg = strlen(this->numeMateriePrima) + 1;
		f.write((char*)&lg, sizeof(int));
		f.write(this->numeMateriePrima, lg);
		f.write((char*)&this->cantitate, sizeof(float));
	}

	void citesteFisierBinar(fstream& f) {
		delete[] this->numeMateriePrima;
		char* buffer;
		int lg = 0;
		f.read((char*)&lg, sizeof(int));
		buffer = new char[lg];
		f.read(buffer, lg);
		this->numeMateriePrima = new char[lg];
		strcpy(this->numeMateriePrima, buffer);
		f.read((char*)&this->cantitate, sizeof(float));
	}

	void scrieFisierText(ofstream& out) {
		out << "\n========= MATERIE PRIMA ============";
		out << "\nNume materie prima: " << this->numeMateriePrima;
		out << "\nCantitate aflata in stoc: " << this->cantitate << endl;
	}

	void citesteFisierText(ifstream& in) {
		delete[] this->numeMateriePrima;
		cout << "\nIntroduceti numele materiei prime: ";
		getchar();
		string buffer;
		getline(in, buffer);
		this->numeMateriePrima = new char[buffer.length() + 1];
		strcpy(this->numeMateriePrima, buffer.data());
		cout << "\nIntroduceti cantitatea: ";
		in >> this->cantitate;
	}

	void exportCSV(int dim, MateriePrima materiiPrime[]) {
		ofstream fileCSV("RaportMateriiPrime.csv", ios::out);

		for (int i = 0; i < dim; i++) {
			fileCSV << "\nNume materie prima: " << materiiPrime[i].getNumeMateriePrima() << ",";
			fileCSV << "\nCantitate ramasa in stoc: " << materiiPrime[i].getCantitate() << ",";
			fileCSV << "\n";
		}

		fileCSV.close();
		cout << "\n----Raport CSV pentru Materii Prime creat----";
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

	int getTimpDePreparare() const {
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

	MateriePrima* getIngrediente() const {
		return this->ingrediente;
	}

	void setNrIngrediente(int nrIngrediente) {
		if (nrIngrediente > 0)
			this->nrIngrediente = nrIngrediente;
		else throw new ExceptieInput("Numarul de ingrediente este negativ!");
	}

	int getNrIngrediente() const {
		return this->nrIngrediente;
	}

	void setGramaje(int nrIngrediente, float* gramajIngrediente) {
		if (nrIngrediente > 0 && gramajIngrediente != nullptr) {
			this->nrIngrediente = nrIngrediente;
			this->gramajIngrediente = new float[this->nrIngrediente];
			for (int i = 0;i < this->nrIngrediente;i++)
				this->gramajIngrediente[i] = gramajIngrediente[i];
		}
	}

	float* getGramajIngrediente() const {
		return this->gramajIngrediente;

	}


	void setNrPortii(int nrPortii) {
		this->nrPortii = nrPortii;
	}

	int getNrPortii() const {
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
		if (p.denumirePreparat != nullptr && strlen(p.denumirePreparat) >= 2) {
			this->denumirePreparat = new char[strlen(p.denumirePreparat) + 1];
			strcpy(this->denumirePreparat, p.denumirePreparat);
		}
		else {
			this->denumirePreparat = nullptr;  // Daca nu exista denumire, setam la nullptr
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

class PreparatVegan : public Preparat {
	bool contineGluten = false;

public:
	PreparatVegan() {}

	PreparatVegan(char* denumirePreparat, int pretPerPortie, Reteta retetaPreparat, bool contineGluten) : Preparat(denumirePreparat, pretPerPortie, retetaPreparat) {
		this->contineGluten = contineGluten;
	}

	PreparatVegan(const PreparatVegan& pv) : Preparat(pv) {
		this->contineGluten = pv.contineGluten;
	}

	PreparatVegan& operator=(const PreparatVegan& pv) {
		if (this != &pv) {
			this->Preparat::operator=(pv);  // Apelam operatorul de atribuire al clasei de baza
			this->contineGluten = pv.contineGluten;
		}
		return *this;
	}

	bool getContineGluten() const {
		return this->contineGluten;
	}

	void setContineGluten(bool contineGluten) {
		this->contineGluten = contineGluten;
	}

	friend ostream& operator<<(ostream& out, const PreparatVegan& pv) {
		out << "\n\n================== PREPARAT VEGAN ========================";
		out << (Preparat&)pv;
		out << "\nContine gluten? --> ";
		if (pv.contineGluten == true)
			out << "Da!";
		else out << "Nu!";
		out << "\n\n================== PREPARAT VEGAN ========================";
		return out;
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

class Utilizator {
public:
	string nume = "N/A";
	string adresa = "N/A";
	string nrTel = "N/A";

	Utilizator(const string nume, const string adresa, const string nrTel) {
		this->nume = nume;
		this->adresa = adresa;
		this->nrTel = nrTel;
	}

	Utilizator() {}

	void setNume(string nume) {
		if (nume.length() > 2) {
			this->nume = nume;
		}
		else throw new ExceptieInput("Nu se poate ca un nume si un prenume sa aiba 2 litere!");
	}

	string getNume() {
		return this->nume;
	}

	void setAdresa(string adresa) {
		if (adresa.length() > 5) {
			this->adresa = adresa;
		}
		else throw new ExceptieInput("Nu se poate ca o adresa sa fie asa scurta!");
	}

	string getAdresa() {
		return this->adresa;
	}

	void setNrTel(string nrTel) {
		if (nrTel.length() > 10 && nrTel.length() < 10) {
			this->nrTel = nrTel;
		}
		else throw new ExceptieInput("Nu se poate ca un nr de telefon sa fie mai mic sau mai mare de 10 caractere!");
	}

	string getNrTel() {
		return this->nrTel;
	}

	~Utilizator() {}
};

void afisare_meniu() {
	cout << endl << endl;
	cout << "Optiunile disponibile din meniu sunt urmatoarele:" << endl;
	cout << "     => afisare_meniu -> afiseaza meniul" << endl;
	cout << "     => adauga_la_comanda -> adauga un preparat la comanda" << endl;
	cout << "     => nota_de_plata -> afiseaza nota de plata" << endl;
	cout << "     => rapoarte -> afiseaza meniul de rapoarte" << endl;
	cout << "     => salvare_txt -> salveaza datele alese in fisier text" << endl;
	cout << "     => salvare_bin -> salveaza datele alese in fisier binar" << endl;
	cout << "     => salvare_csv -> salveaza datele alese in fisier CSV" << endl;
	cout << "     => consultare_materii_prime -> citeste dintr-un fisier binar/text materiile prime" << endl;
	cout << "     => iesire -> parasiti meniul" << endl;
	cout << "Introduceti comanda dorita:" << endl;
}

void afisare_meniu_preparate() {
	cout << "\n\n=========PREPARATELE NOASTRE========";
	cout << "\n   1->Pizza Margherita";
	cout << "\n   2->Paste Carbonara";
	cout << "\n   3->Omleta cu ciuperci";
	cout << "\n   4->Pizza Quattro Formaggi";
	cout << "\n   5->Supa de ceapa";
	cout << "\n   6->Placinta cu mere";
	cout << "\n   7->Pui Tikka Masala";
	cout << "\n   8->Salata Caesar";
	cout << "\n   9->Preparat Vegan cu Rosii si Ardei";
	cout << "\n   10->Preparat Vegan cu Cartofi si Ciuperci";
	cout << "\n   0->IESIRE";
	cout << "\n======================================" << endl << endl;
}

void rapoarte() {
	cout << "\nmaterii_prime -> Raport afisare materii prime";
	cout << "\nafisare_retete -> Raport afisare retete";
	cout << "\nafisare_preparate_vegane -> Raport ce afiseaza preparatele vegane" << endl;

}

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
	Reteta PizzaMargherita(30, 5, ingredientePizzaMargherita, gramajePizzaMargherita, 1);
	char pizzaMargherita[] = "Pizza Margherita";
	Preparat PizzaMargherita1(pizzaMargherita, 30, PizzaMargherita);
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
	Reteta OmletaCiuperci(15, 5, ingredienteOmletaCiuperci, gramajeOmletaCiuperci, 1);
	char omletaCiuperci[] = "Omleta cu Ciuperci";
	Preparat OmletaCiuperci1(omletaCiuperci, 20, OmletaCiuperci);
	cout << "\n\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
	cout << OmletaCiuperci1;
	cout << "\n\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";

	// Pizza Quattro Formaggi
	MateriePrima ingredienteQuattroFormaggi[] = { aluat1, sosRosii1, mozzarella1, parmezan1, branzaTelemea1 };
	float gramajeQuattroFormaggi[] = { 300, 150, 200, 50, 50 };
	Reteta QuattroFormaggi(35, 5, ingredienteQuattroFormaggi, gramajeQuattroFormaggi, 1);
	char pizzaQuattroFormaggi[] = "Pizza Quattro Formaggi";
	Preparat QuattroFormaggi1(pizzaQuattroFormaggi, 40, QuattroFormaggi);
	cout << "\n\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
	cout << QuattroFormaggi1;
	cout << "\n\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";

	// Supa de ceapa
	MateriePrima ingredienteSupaCeapa[] = { ceapa1, unt1, sare1, piper1 };
	float gramajeSupaCeapa[] = { 200, 30, 5, 2 };
	Reteta SupaCeapa(30, 4, ingredienteSupaCeapa, gramajeSupaCeapa, 1);
	char supaCeapa[] = "Supa de Ceapa";
	Preparat SupaCeapa1(supaCeapa, 35, SupaCeapa);
	cout << "\n\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
	cout << SupaCeapa1;
	cout << "\n\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";

	// Placinta cu mere
	MateriePrima ingredientePlacintaMere[] = { aluat1, mere1, zahar1, scortisoara1, unt1 };
	float gramajePlacintaMere[] = { 250, 400, 100, 5, 30 };
	Reteta PlacintaMere(40, 5, ingredientePlacintaMere, gramajePlacintaMere, 1);
	char placintaMere[] = "Placinta cu Mere";
	Preparat PlacintaMere1(placintaMere, 50, PlacintaMere);
	cout << "\n\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
	cout << PlacintaMere1;
	cout << "\n\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";

	// Pui Tikka Masala
	MateriePrima ingredientePuiTikkaMasala[] = { pui1, rosii1, ceapa1, usturoi1, ghimbir1, iaurt1, curry1, coriandru1, sare1, piper1 };
	float gramajePuiTikkaMasala[] = { 300, 250, 150, 10, 10, 100, 20, 5, 3, 3 };
	Reteta PuiTikkaMasala(45, 10, ingredientePuiTikkaMasala, gramajePuiTikkaMasala, 1);
	char puiTikkaMasala[] = "Pui Tikka Masala";
	Preparat PuiTikkaMasala1(puiTikkaMasala, 55, PuiTikkaMasala);
	cout << "\n\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
	cout << PuiTikkaMasala1;
	cout << "\n\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";

	// Salata Caesar
	MateriePrima ingredienteSalataCaesar[] = { pui1, salata1, crutoane1, parmezan1, sosCaesar1 };
	float gramajeSalataCaesar[] = { 200, 150, 50, 30, 50 };
	Reteta SalataCaesar(20, 5, ingredienteSalataCaesar, gramajeSalataCaesar, 1);
	char salataCaesar[] = "Salata Caesar";
	Preparat SalataCaesar1(salataCaesar, 25, SalataCaesar);
	cout << "\n\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
	cout << SalataCaesar1;
	cout << "\n\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";

	// Preparat Vegan cu Rosii si Ardei
	MateriePrima ingredienteVegan1[] = { rosii1, ardei1, uleiDeMasline1 };
	float gramajeVegan1[] = { 200, 100, 20 };
	Reteta Vegan1(30, 3, ingredienteVegan1, gramajeVegan1, 1);
	char preparatVegan1[] = "Preparat Vegan cu Rosii si Ardei";
	PreparatVegan VeganCuRosiiSiArdei(preparatVegan1, 25, Vegan1, false);
	cout << "\n\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
	cout << VeganCuRosiiSiArdei;
	cout << "\n\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";


	// Preparat Vegan cu Cartofi si Ciuperci
	MateriePrima ingredienteVegan2[] = { cartofi1, ciuperci1, ceapa1, uleiDeMasline1 };
	float gramajeVegan2[] = { 150, 100, 50, 30 };
	Reteta Vegan2(40, 4, ingredienteVegan2, gramajeVegan2, 1);
	char preparatVegan2[] = "Preparat Vegan cu Cartofi si Ciuperci";
	PreparatVegan VeganCuCartofiSiCiuperci(preparatVegan2, 30, Vegan2, true);
	cout << "\n\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
	cout << VeganCuCartofiSiCiuperci;
	cout << "\n\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";

	char codMasa[] = "2AB33";
	Comanda comanda;

	string comandaTastatura;
	int ok = -1;

	do {
		afisare_meniu();
		getline(cin, comandaTastatura);

		if (comandaTastatura == "afisare_meniu") {
			afisare_meniu_preparate();
		}

		if (comandaTastatura == "adauga_la_comanda")
		{

			cout << "\n\nAdaugati la comanda:\n\n";
			cin >> ok;
			switch (ok) {
			case 1:
				comanda.adaugaPreparat(PizzaMargherita1, 1);
				break;
			case 2:
				comanda.adaugaPreparat(SpaghettiCarbonara1, 1);
				break;
			case 3:
				comanda.adaugaPreparat(OmletaCiuperci1, 1);
				break;
			case 4:
				comanda.adaugaPreparat(QuattroFormaggi1, 1);
				break;
			case 5:
				comanda.adaugaPreparat(SupaCeapa1, 1);
				break;
			case 6:
				comanda.adaugaPreparat(PlacintaMere1, 1);
				break;
			case 7:
				comanda.adaugaPreparat(PuiTikkaMasala1, 1);
				break;
			case 8:
				comanda.adaugaPreparat(SalataCaesar1, 1);
				break;
			case 9:
				comanda.adaugaPreparat(VeganCuRosiiSiArdei, 1);
				break;
			case 10:
				comanda.adaugaPreparat(VeganCuCartofiSiCiuperci, 1);
				break;
			}
		}
		if (comandaTastatura == "nota_de_plata") {
			comanda.nota_de_plata();
		}

		if (comandaTastatura == "rapoarte") {
			rapoarte();
		}

		if (comandaTastatura == "materii_prime") {
			//raport cu vector, afiseaza materii prime
			vector<MateriePrima> v1;
			v1.push_back(scortisoara1);
			v1.push_back(ghimbir1);
			v1.push_back(pui1);
			v1.push_back(salata1);
			v1.push_back(rosii1);


			ofstream Raport1;
			Raport1.open("RaportMateriiPrime.txt");


			for (const auto& mp : v1) {
				Raport1 << mp << endl;
			}

			Raport1.close();
		}

		if (comandaTastatura == "afisare_retete") {
			// Raport cu vector, afiseaza retete
			vector<Reteta> reteteVector;
			reteteVector.push_back(PizzaMargherita);
			reteteVector.push_back(SpaghettiCarbonara);
			reteteVector.push_back(OmletaCiuperci);
			reteteVector.push_back(QuattroFormaggi);
			reteteVector.push_back(SupaCeapa);
			reteteVector.push_back(PlacintaMere);
			reteteVector.push_back(PuiTikkaMasala);
			reteteVector.push_back(SalataCaesar);

			ofstream Raport2;
			Raport2.open("RaportRetete.txt");

			for (const auto& reteta : reteteVector) {
				Raport2 << "\nTimp de prearare: " << reteta.getTimpDePreparare() << endl;
				Raport2 << "\nNr Ingrediente: " << reteta.getNrIngrediente() << " ";
				const MateriePrima* ingrediente = reteta.getIngrediente();
				const float* gramaje = reteta.getGramajIngrediente();
				Raport2 << "\n\n ===================== >> Ingrediente << ===================== " << endl;
				for (int i = 0; i < reteta.getNrIngrediente(); i++) {
					Raport2 << "\n ==> Ingredientul " << i + 1 << ":" << endl;
					Raport2 << ingrediente[i] << endl;
					Raport2 << "Cantitatea necesara: ";
					Raport2 << gramaje[i] << endl;
				}
				Raport2 << reteta.getNrPortii() << endl;
			}
			Raport2.close();
		}

		if (comandaTastatura == "afisare_preparate_vegane") {
			ofstream RaportVegane;
			RaportVegane.open("RaportReteteVegane.txt");

			vector<PreparatVegan> preparateVegane;

			preparateVegane.push_back(VeganCuCartofiSiCiuperci);
			preparateVegane.push_back(VeganCuRosiiSiArdei);

			for (const auto& preparat : preparateVegane) {
				RaportVegane << "\n\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
				RaportVegane << preparat;
				RaportVegane << "\n\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
			}

			RaportVegane.close();
		}

		if (comandaTastatura == "salvare_txt") {
			//scriere de materii prime in fisier text
			ofstream fout("MateriiPrime.txt");
			if (fout.is_open()) {
				scortisoara1.scrieFisierText(fout);
				ghimbir1.scrieFisierText(fout);
				mere1.scrieFisierText(fout);

				fout.close();
				cout << "\n\nDatele au fost scrise in fisierul text!\n";
			}
			else {
				throw new ExceptieInput("\n\nDatele nu au putut fi scrise!!");
				return -2;
			}
		}

		if (comandaTastatura == "salvare_bin") {
			fstream fisierBinar("MateriiPrime.bin", ios::binary | ios::out);
			if (fisierBinar.is_open()) {
				scortisoara1.scrieFisierBinar(fisierBinar);
				ghimbir1.scrieFisierBinar(fisierBinar);
				mere1.scrieFisierBinar(fisierBinar);
				fisierBinar.close();
			}
			else {
				throw new ExceptieInput("Eroare la deschiderea fisierului binar.\n");
				return -1;
			}
		}

		if (comandaTastatura == "salvare_CSV") {

			int dim = 3;
			MateriePrima materiiPrime[3] = { ghimbir1, mere1, scortisoara1 };
			ofstream fisierCSV("RaportMateriiPrime.csv", ios::out);
			for (int i = 0; i < dim; i++) {
				materiiPrime[i].exportCSV(3, materiiPrime);
			}
			fisierCSV.close();

		}

		//if (comandaTastatura == "import_csv_materii_prime") {
		//	ifstream fisierCSV("MateriiPrime.csv");
		//	if (!fisierCSV.is_open()) {
		//		throw new ExceptieInput("Eroare la deschiderea fisierului CSV.\n");
		//		return -1;
		//	}
		//	char temp[] = {" "};
		//	MateriePrima mp(temp, 0); // Initializam un obiect temporar
		//	while (fisierCSV >> mp.getNumeMateriePrima()) {
		//		getchar(); // Consumãm newline-ul
		//		fisierCSV >> mp.getCantitate();
		//		cout << "Materie Prima citita: " << mp << endl;
		//	}
		//}

		if (comandaTastatura == "consultare_materii_prime") {
			cout << "\n\nAlegeti optiunea: (1->binar, 2->text)";
			int i;
			cin >> i;
			fstream fisierBinar1("MateriiPrime.bin", ios::binary | ios::in);
			ifstream fin("MateriiPrime.txt");
			MateriePrima scortisoara2, ghimbir2, mere2;

			switch (i) {
			case 1:
				//citire de materii prime din fisier binar
				// Citire din fisierul binar
				scortisoara2.citesteFisierBinar(fisierBinar1);
				ghimbir2.citesteFisierBinar(fisierBinar1);
				mere2.citesteFisierBinar(fisierBinar1);
				// Afisare informatii citite din fisierul binar
				cout << scortisoara2 << endl;
				cout << ghimbir2 << endl;
				cout << mere2 << endl;
				fisierBinar1.close();
				break;


			case 2:
				// citirea de materii prime din fisier text
				if (fin.is_open()) {
					MateriePrima cititScortisoara;
					cititScortisoara.citesteFisierText(fin);
					MateriePrima cititGhimbir;
					cititGhimbir.citesteFisierText(fin);
					MateriePrima cititMere;
					cititMere.citesteFisierText(fin);
					fin.close();
					cout << "Materie Prima citita:\n";
					cout << cititScortisoara << endl;
					cout << cititGhimbir << endl;
					cout << cititMere << endl;
				}
				fin.close();
				break;
			}


		}


		if (comandaTastatura == "iesire")
			ok = 0;
	} while (ok != 0);


	return 0;
}
