-- MySQL dump 10.13  Distrib 5.7.17, for Linux (x86_64)
--
-- Host: localhost    Database: JuegoPokemon
-- ------------------------------------------------------
-- Server version	5.7.17-0ubuntu0.16.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Current Database: `JuegoPokemon`
--

DROP DATABASE IF EXISTS `JuegoPokemon` /*!40100 DEFAULT CHARACTER SET latin1 */;

USE `JuegoPokemon`;

--
-- Table structure for table `Jugadores`
--

DROP TABLE IF EXISTS `Jugadores`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Jugadores` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `nombre` varchar(20) DEFAULT NULL,
  `pasword` varchar(20) DEFAULT NULL,
  `numeroPokemons` int(11) DEFAULT NULL,
  `victorias` int(11) DEFAULT NULL,
  `derrotas` int(11) DEFAULT NULL,
  `pos` text,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Jugadores`
--

LOCK TABLES `Jugadores` WRITE;
/*!40000 ALTER TABLE `Jugadores` DISABLE KEYS */;
INSERT INTO `Jugadores` VALUES (1,'Ash','pikachu123',3,20,5,'Pueblo Paleta'),(2,'Misty','aguaPura',2,15,8,'Ciudad Celeste'),(3,'Brock','rocaFuerte',2,17,6,'Ciudad Plateada'),(4,'Marti','123',0,0,0,''),(5,'adios','123',0,0,0,'');
/*!40000 ALTER TABLE `Jugadores` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Partidas`
--

DROP TABLE IF EXISTS `Partidas`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Partidas` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `fecha` int(11) DEFAULT NULL,
  `jugador1` varchar(20) DEFAULT NULL,
  `jugador2` varchar(20) DEFAULT NULL,
  `jugador3` varchar(20) DEFAULT NULL,
  `jugador4` varchar(20) DEFAULT NULL,
  `ganador` varchar(20) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Partidas`
--

LOCK TABLES `Partidas` WRITE;
/*!40000 ALTER TABLE `Partidas` DISABLE KEYS */;
INSERT INTO `Partidas` VALUES (1,20240301,'Ash','Misty','Brock','Gary','Ash'),(2,20240302,'Red','Blue','Leaf','Ethan','Red'),(3,20240303,'Serena','Clemont','Bonnie','Alain','Alain');
/*!40000 ALTER TABLE `Partidas` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Pokedex`
--

DROP TABLE IF EXISTS `Pokedex`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Pokedex` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `nombrePokemon` varchar(20) DEFAULT NULL,
  `ataquees` text,
  `hp` int(11) DEFAULT NULL,
  `elmento` int(11) DEFAULT NULL,
  `debilidad` int(11) DEFAULT NULL,
  `fortaleza` int(11) DEFAULT NULL,
  `fase` text,
  `descripcion` text,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Pokedex`
--

LOCK TABLES `Pokedex` WRITE;
/*!40000 ALTER TABLE `Pokedex` DISABLE KEYS */;
INSERT INTO `Pokedex` VALUES (1,'Pikachu','Impactrueno*40*20*Ataque eléctrico rápido',35,4,5,0,'FASE1(1)','Ratón eléctrico veloz'),(2,'Charmander','Ascuas*30*15*Llamas débiles',39,1,2,6,'FASE1(2),FASE2(5),FASE3(6)','Lagarto de fuego'),(3,'Squirtle','Pistola Agua*35*15*Chorro de agua',44,2,4,1,'FASE1(3),FASE2(8),FASE3(9)','Tortuga acuática');
/*!40000 ALTER TABLE `Pokedex` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Relacio`
--

DROP TABLE IF EXISTS `Relacio`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Relacio` (
  `IdJ` int(11) NOT NULL,
  `IdP` int(11) NOT NULL,
  `Nivell` int(11) DEFAULT NULL,
  PRIMARY KEY (`IdJ`,`IdP`),
  KEY `IdP` (`IdP`),
  CONSTRAINT `Relacio_ibfk_1` FOREIGN KEY (`IdJ`) REFERENCES `Jugadores` (`id`) ON DELETE CASCADE,
  CONSTRAINT `Relacio_ibfk_2` FOREIGN KEY (`IdP`) REFERENCES `Pokedex` (`id`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Relacio`
--

LOCK TABLES `Relacio` WRITE;
/*!40000 ALTER TABLE `Relacio` DISABLE KEYS */;
INSERT INTO `Relacio` VALUES (1,1,7),(2,2,5),(3,3,9);
/*!40000 ALTER TABLE `Relacio` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2025-03-29 13:21:54
