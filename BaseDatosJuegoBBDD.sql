DROP DATABASE IF EXISTS JuegoPokemon;
CREATE DATABASE JuegoPokemon;

USE JuegoPokemon;

CREATE TABLE Partidas (
    id INT AUTO_INCREMENT PRIMARY KEY NOT NULL,
    fecha INT,
    jugador1 VARCHAR(20),
    jugador2 VARCHAR(20),
    jugador3 VARCHAR(20),
    jugador4 VARCHAR(20),
    ganador VARCHAR(20)
) ENGINE=InnoDB;

INSERT INTO Partidas (fecha, jugador1, jugador2, jugador3, jugador4, ganador) VALUES
(20240301, 'Ash', 'Misty', 'Brock', 'Gary', 'Ash'),
(20240302, 'Red', 'Blue', 'Leaf', 'Ethan', 'Red'),
(20240303, 'Serena', 'Clemont', 'Bonnie', 'Alain', 'Alain');

CREATE TABLE Pokedex (
    id INT AUTO_INCREMENT PRIMARY KEY NOT NULL,
    nombrePokemon VARCHAR(20),
    ataquees TEXT, -- nombre del ataque*daño*energia*descripción,(ataque2)
    hp INT,
    elmento INT, -- 0 normal, 1 fuego, 2 agua, 3 planta, 4 rayo, 5 tierra, 6 psíquico
    debilidad INT, -- ''
    fortaleza INT, -- ''
    fase TEXT, -- FASE1(ID),FASE2(ID),FASE3(ID),(...)
    descripcion TEXT 
) ENGINE=InnoDB;

INSERT INTO Pokedex (nombrePokemon, ataquees, hp, elmento, debilidad, fortaleza, fase, descripcion) VALUES
('Pikachu', 'Impactrueno*40*20*Ataque eléctrico rápido', 35, 4, 5, 0, 'FASE1(1)', 'Ratón eléctrico veloz'),
('Charmander', 'Ascuas*30*15*Llamas débiles', 39, 1, 2, 6, 'FASE1(2),FASE2(5),FASE3(6)', 'Lagarto de fuego'),
('Squirtle', 'Pistola Agua*35*15*Chorro de agua', 44, 2, 4, 1, 'FASE1(3),FASE2(8),FASE3(9)', 'Tortuga acuática');

CREATE TABLE Jugadores (
    id INT AUTO_INCREMENT PRIMARY KEY NOT NULL,
    nombre VARCHAR(20),
    pasword VARCHAR(20),
    numeroPokemons INT,
    nivel INT,
    pokemons TEXT, -- Lista de IDs separada por comas y nivel separado por *
    victorias INT,
    derrotas INT,
    pos TEXT
) ENGINE=InnoDB;

INSERT INTO Jugadores (nombre, pasword, numeroPokemons, nivel, pokemons, victorias, derrotas, pos) VALUES
('Ash', 'pikachu123', 3, 10, '25*5,4*6,7*4', 20, 5, 'Pueblo Paleta'),
('Misty', 'aguaPura', 2, 8, '7*7,8*5', 15, 8, 'Ciudad Celeste'),
('Brock', 'rocaFuerte', 2, 9, '74*8,95*6', 17, 6, 'Ciudad Plateada');