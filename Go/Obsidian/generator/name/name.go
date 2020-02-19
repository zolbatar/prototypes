package namegenerator

import (
	"math/rand"
)

type NameGenerator struct {
	rand      *rand.Rand
	language  string
	FirstName []string
	LastName  []string
}

func New(language string, r *rand.Rand) *NameGenerator {
	switch language {
	case "French":
		return &NameGenerator{
			rand:     r,
			language: language,
			FirstName: []string{
				"Alain", "Anton", "Bernard", "Franck", "Henri", "Isaac", "Julien", "Marcel", "Philippe", "Pierre",
				"Serge", "Tristan", "Yves", "Zacharie", "Laurent", "Bruno", "Agathe", "Aurore", "Brigitte", "Claudine",
				"Emmanuelle", "Isabelle", "Josette", "Laure", "Maryse", "Odette", "Sabine", "Somone", "Virginie", "Slyvie",
			},
			LastName: []string{
				"Allard", "Baudin", "Bisset", "Daniau", "Couture", "Denis", "Foss", "Germain", "Faucher", "Gagnon",
				"Herriot", "Giroux", "Janvier", "Lambert", "Langlais", "Leroy", "Martel", "Paget", "Morin", "Monette",
				"Pelletier", "Page", "Roche", "Salomon", "Samson", "Reyer", "Thibault", "Tobias", "Yount", "Travert",
			},
		}
	case "German":
		return &NameGenerator{
			rand:     r,
			language: language,
			FirstName: []string{
				"Johan", "David", "Paul", "Peter", "Michael", "Georg", "Eduard", "Björn", "Philipp", "Wilfried",
				"Ben", "Alex", "Sven", "Stefan", "Robert", "Klara", "Melanie", "Johanna", "Jennifer", "Linda",
				"Alexandra", "Melissa", "Barbara", "Marie", "Sarah", "Susanne", "Julia", "Andrea", "Julia", "Marianne",
			},
			LastName: []string{
				"Smitz", "Müller", "Meier", "Schulz", "Welting", "Portmann", "Fischer", "Thon", "Lehmann", "Roth",
				"Huber", "Höhne", "Bruns", "Wesseling", "Decker", "Engelhardt", "Essing", "Gastrop", "Gericke", "Holz",
				"Hermann", "Heinrich", "Hiebing", "Bettermann", "Lensing", "Richter", "Schneider", "Radermacher", "Rose", "Riemer",
			},
		}
	case "Spanish":
		return &NameGenerator{
			rand:     r,
			language: language,
			FirstName: []string{
				"Antonio", "Jose", "Manuel", "Francisco", "Juan", "David", "Jose Antonio", "Jose Luis", "Javier", "Jesus",
				"Francisco Javier", "Carlos", "Daniel", "Miguel ", "Rafael", "Jose Manuel", "Pedro", "Alejandro", "Angel",
				"Miguel Angel", "Jose Maria", "Fernando", "Luis", "Pablo", "Sergio", "Jorge", "Alberto", "Juan Carlos",
				"Juan Jose", "Ramon", "Enrique", "Diego", "Juan Antonio", "Vicente", "Alvaro", "Raul", "Adrian", "Joaquin",
				"Ivan", "Andres", "Oscar", "Ruben", "Juan Manuel", "Santiago", "Eduardo", "Victor", "Roberto", "Jaime",
				"Francisco Jose", "Ignacio", "Carmen", "Maria", "Diana", "Josefina", "Isabel", "Ana Maria", "Dolores",
				"Pilar", "Teresa", "Ana", "Laura", "Antonia", "Marta", "Almudena", "Ricardo", "Emilio", "Julio", "Gabriel",
				"Salvador", "Mario", "Julian", "Marcos", "Tomas", "Agustin", "Felix", "Guillermo", "Jordi", "Josep",
				"Cesar", "Joan", "Carmelo", "Domingo", "Gonzalo", "Mariano", "Felipe", "Martin", "Alfredo", "Nicolas",
				"Salvador", "Mariano", "Marc", "Ismael", "Hugo", "Samuel", "Hector", "Alfonso", "Salvador", "Ricardo",
				"Mario", "Jordi",
			},
			LastName: []string{
				"Garcia", "Gonzalez", "Rodriguez", "Fernandez", "Lopez", "Martines", "Sanchez", "Perez", "Gomez", "Martin",
				"Jimenez", "Ruiz", "Hernandez", "Diaz", "Moreno", "Alvarez", "Muñoz", "Romero", "Alonso", "Gutierrez",
				"Navarro", "Torres", "Dominguez", "Vazquez", "Ramos", "Gil", "Ramirez", "Serrano", "Blanco", "Suarez",
				"Molina", "Morales", "Ortega", "Delgado", "Castro", "Ortiz", "Rubio", "Marin", "Sanz", "Nuñez", "Iglesias",
				"Medina", "Garrido", "Santos", "Castillo", "Cortes", "Lozano", "Guerrero", "Cano", "Prieto", "Mendez",
				"Calvo", "Cruz", "Gallego", "Vidal", "Leon", "Herrera", "Marquez", "Peña", "Cabrera", "Flores", "Campos",
				"Vega", "Diez", "Fuentes", "Carrasco", "Caballero", "Nieto", "Reyes", "Aguilar", "Pascual", "Herrero",
				"Santana", "Lorenzo", "Hidalgo", "Montero", "Ibañez", "Gimenez", "Ferrer", "Duran", "Vicente", "Benitez",
				"Morales", "Santiago", "Arias", "Vargas", "Carmona", "Crespo", "Roman", "Pastor", "Soto", "Saez", "Velasco",
				"Soler", "Moya", "Esteban", "Parra", "Bravo", "Gallardo", "Rojas",
			},
		}
	case "Korean":
		return &NameGenerator{
			rand:     r,
			language: language,
			FirstName: []string{
				"Bae", "Chin", "Choon-Hee", "Eun", "Gook", "Jin", "Kang-Dae", "Kyu", "Moon", "Mun-Hee",
				"Sang-Ook", "Shin", "Whan", "Yong-Sun", "Young-Soo", "Ae-Che", "Bong", "Chin-Sun", "Du", "Gi",
				"Goo", "Haneul", "Kwan", "Kyung", "Mi-Ok", "Shik", "Soon-Bok", "Sun-Hi", "Yoon", "Young-Soon",
			},
			LastName: []string{
				"Gan", "Gang", "Gok", "Namgung", "Nu", "Mangjeol", "Min", "Bok", "Sagong", "Su",
				"Ya", "Eo", "Yeom", "Ong", "Lee", "Lee", "Kim", "Kim", "Park", "Park",
				"Lee", "Kim", "Park", "Rim", "Jong", "Tan", "Pyeong", "Ho", "Hwang", "Pi",
			},
		}
	}

	// Fall back to English
	return &NameGenerator{
		rand:     r,
		language: "English",
		FirstName: []string{
			"John", "David", "Paul", "Peter", "Michael", "George", "Edward", "Brian", "Philip", "William",
			"Ben", "Alex", "Jeremy", "Steven", "Robert", "Claire", "Molly", "Jennifer", "Joanne", "Linda",
			"Amelia", "Melissa", "Barbara", "Zoe", "Sarah", "Sally", "Julia", "Brenda", "Zara", "Jessica",
		},
		LastName: []string{
			"Smith", "Jones", "Taylor", "Williams", "Brown", "Davies", "Evans", "Wilson", "Thomas", "Roberts",
			"Johnson", "Lewis", "Walker", "Robinson", "Wood", "Thompson", "White", "Watson", "Jackson", "Wright",
			"Green", "Harris", "Cooper", "King", "Lee", "Martin", "Clarke", "James", "Morgan", "Hughes",
		},
	}
}

func Generate(ng *NameGenerator) (*NameGenerator, string, string, string) {
	if len(ng.FirstName) == 0 || len(ng.LastName) == 0 {
		ng = New(ng.language, ng.rand)
	}
	ifn := ng.rand.Intn(len(ng.FirstName))
	iln := ng.rand.Intn(len(ng.LastName))
	fn := ng.FirstName[ifn]
	ln := ng.LastName[iln]
	return ng, fn, ln, fn + " " + ln
}
