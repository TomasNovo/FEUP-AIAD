#include "bus_stop.h"

const string& Bus_Stop::GetName() const
{
	return name;
}

unsigned int Bus_Stop::GetLinesCount() const
{
	return linesAtStop.size();
}

void Bus_Stop::RemoveLineFromStop(const Line *ptr_Line )
{
	auto iterator = find(linesAtStop.begin(), linesAtStop.end(), ptr_Line);
	if (iterator != linesAtStop.end()) { // found
		linesAtStop.erase(iterator);
	}
	//if it doesn't exist do nothing
}

const vector<Line*>& Bus_Stop::GetLines() const
{
	return linesAtStop;
}

void Bus_Stop::AddLine(Line * ptr_Line)
{
	linesAtStop.push_back(ptr_Line);
}

void Bus_Stop::ShowSchedule() const
{ // REQUIRES MASSIVE TRANSLATION TO ENGLISH ## WILL BE LEFT IN PORTUGUESE FOR THE TIME BEING
	for (Line* line : linesAtStop) { // Iterar sobre cada linha que passa na paragem.
		const unsigned int freq = line->GetFreq(); // frequencia da linha
												//Calcular tempo entre a primeira paragem e a paragem que queremos obter os horarios
		const unsigned int bus_stop_number = GetBus_StopNumber(line->GetBus_Stops(), this->GetName());
		const unsigned int offset = CalculateOffset(line->GetTimeBetweenStops(), bus_stop_number);

		const unsigned int number_of_bus_stops = line->GetBus_Stops().size();
		// Mostrar no sentido de ida
		if (this->GetName() != line->GetBus_Stops()[number_of_bus_stops - 1]) { // is not the last stop
			cout << endl;
			cout << setw(5) << "Schedule of the Line " << line->GetID() << " in the direction " << line->GetBus_Stops()[0] << " -> " << line->GetBus_Stops()[number_of_bus_stops - 1] << " :" << endl;
			PrintSpecificSchedule(SCHEDULE_START, SCHEDULE_END, offset, freq);
			cout << endl;
		}

		if (this->GetName() != line->GetBus_Stops()[0]) { // is not the first stop
			cout << endl;
			// Mostrar no sentido de volta
			const unsigned int tempoViagemTotal = CalculateOffset(line->GetTimeBetweenStops(), number_of_bus_stops - 1);
			cout << setw(5) << "Schedule of the Line " << line->GetID() << " in the direction " << line->GetBus_Stops()[number_of_bus_stops - 1] << " -> " << line->GetBus_Stops()[0] << " :" << endl;
			PrintSpecificSchedule(SCHEDULE_START, SCHEDULE_END, tempoViagemTotal + (tempoViagemTotal - offset), freq);
			cout << endl;
		}
	}
}

Bus_Stop::Bus_Stop(const string & argBus_StopName)
{
	name = argBus_StopName;
}

int Bus_Stop::GetBus_StopNumber(const vector<string>& vec_Bus_Stops, const string & Bus_Stop_Name)
{
	for (size_t i = 0; i < vec_Bus_Stops.size(); i++) {
		if (vec_Bus_Stops[i] == Bus_Stop_Name) {
			return i;
		}
	}
	return -1; // vamos esperar que isto nao aconteça...
}

int Bus_Stop::CalculateOffset(const vector<unsigned int> timeBetweenStops, const unsigned int & Bus_Stop_Number)
{
	unsigned int acumulator = 0;
	for (unsigned int i = 0; i < Bus_Stop_Number; i++) {
		acumulator += timeBetweenStops[i];
	}
	return acumulator;
}


void Bus_Stop::PrintSpecificSchedule(const unsigned int &Start, const unsigned int &End, const unsigned int &offset, const unsigned int &freq)
{ // Translate this someday...
	unsigned int horas = Start, minutos = 0;
	while (true) {
		if (minutos >= 60) {
			horas += minutos / 60;
			minutos %= 60;
			if (End <= horas)
				return;
		}

		unsigned int horasLoop = horas;
		unsigned int minutosLoop = minutos + offset;
		if (minutosLoop >= 60) horasLoop += minutosLoop / 60;
		minutosLoop %= 60;
		cout << horasLoop << ":";
		if (minutosLoop < 10) cout << "0";
		cout << minutosLoop << " ";
		minutos += freq;
	}
}