#include "line.h"

void Line::SetID(const string& input)
{
	ID = input;
}

void Line::SetFreq(const unsigned int& input)
{
	freq = input;
}

void Line::SetBus_Stops(const vector<string>& input)
{
	bus_stops = input;
}

void Line::SetTimeBetweenStops(const vector<unsigned int>& input)
{
	timeBetweenStops = input;
}


string Line::GetID() const
{
	return ID;
}

unsigned int Line::GetFreq() const
{
	return freq;
}

const vector<string>& Line::GetBus_Stops() const
{
	return bus_stops;
}

vector<unsigned int> Line::GetTimeBetweenStops() const
{
	return timeBetweenStops;
}


void Line::ShowSchedule() const
{ // SEMI-TRANSLATED....
	//Show forward direction
	cout << setw(5) << "" << "Direction " << bus_stops[0] << " -> " << bus_stops[bus_stops.size() - 1] << " :" << endl << endl;
	PrintSpecificSchedule(bus_stops, timeBetweenStops, freq, 0);
	cout << endl << endl;

	//Show return direction
	vector<string> vec_paragens = bus_stops;
	vector<unsigned int> vec_tempoViagem = timeBetweenStops;

	// // Calcular o offset inicial, isto é, o tempo que o primeiro autocarro do dia demora a fazer o percurso de ida
	const unsigned int offset = abs(CalculateOffset(vec_tempoViagem, vec_paragens.size() - 1));

	reverse(vec_paragens.begin(), vec_paragens.end()); // Alterar a ordem do vetor para o inverso para imprimir o horario de VOLTA
	reverse(vec_tempoViagem.begin(), vec_tempoViagem.end()); // ""
	cout << setw(5) << "" << "Direction " << bus_stops[bus_stops.size() - 1] << " -> " << bus_stops[0] << " :" << endl << endl;
	PrintSpecificSchedule(vec_paragens, vec_tempoViagem, freq, offset);
}

void Line::PrintSpecificSchedule(const vector<string>& bus_stops, const vector<unsigned int>& timeBetweenStops, unsigned int freq, unsigned int offset)
{ // REQUIRES TRANSLATION SOMEWHERE DOWN THE ROAD
	vector<unsigned int> widthColumns;
	//Calculate width and printer header first
	for (const string& bus_stop : bus_stops) {
		widthColumns.push_back(bus_stop.length() + 1);
		cout << setw(bus_stop.length() + 4) << bus_stop;
	}
	cout << endl;
	unsigned int horasTurno = SCHEDULE_START, minutosTurno = offset;
	while (horasTurno < SCHEDULE_END) {
		unsigned int horasLinha = horasTurno, minutosLinha = minutosTurno;
		for (size_t i = 0; i < bus_stops.size(); i++) {
			cout << setw(widthColumns[i]) << horasLinha << ":";
			if (minutosLinha < 10)	cout << "0";
			cout << minutosLinha;

			if (!(i == bus_stops.size() - 1)) {  //isto 'e, se a iteracao ainda nao chegou 'a ultima paragem
				minutosLinha += timeBetweenStops[i];
				if (minutosLinha >= 60) {
					horasLinha += minutosLinha / 60;
					minutosLinha %= 60;
				}
			}
		}

		minutosTurno += freq;
		if (minutosTurno >= 60) {
			horasTurno += minutosTurno / 60;
			minutosTurno %= 60;
		}
		cout << endl;
	}
}

int Line::CalculateOffset(const vector<unsigned int> timeBetweenStops, const unsigned int & Bus_Stop_Number)
{
	unsigned int acumulator = 0;
	for (unsigned int i = 0; i < Bus_Stop_Number; i++) {
		acumulator += timeBetweenStops[i];
	}
	return acumulator;
}