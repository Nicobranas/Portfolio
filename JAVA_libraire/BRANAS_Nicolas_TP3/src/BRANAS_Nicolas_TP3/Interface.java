package BRANAS_Nicolas_TP3;
import java.util.*;

public class Interface {
	
	public static void main(String[] args) {
		
		Scanner sc = new Scanner(System.in);
		System.out.println("pour des question de facilite et de rapidite de conception du code, "
				+ "les variables non commune aux medium (comme le numero d'articles, auteur, etc) seront "
				+ "initialises a une valeur par default, ainsi que la date de parution");
		
		Mediatheque mediatheque = new Mediatheque();
		
		/**
		 * boucle infini qui pose les questions
		 */
		while(true) {
			
			System.out.println("nouveau medium:");
			System.out.println("titre");
			String titre=sc.nextLine();
			System.out.println("auteur");
			String auteur=sc.nextLine();
			System.out.println("CD DVD Livre ou Article?");
			String type=sc.nextLine();
			
			if (type.equals("DVD")) {
				//ici on devrait demander les param specifique, sans oublie de rajouter un constructeur qui prend tout les parametre en compte
				DVD med = new DVD(titre,auteur);
				mediatheque.ajouter(med);
			}
			else if (type.equals("CD")) {
				//meme remarque que pour DVD
				CD med = new CD(titre,auteur);
				mediatheque.ajouter(med);
			}
			else if (type.equals("Livre")) {
				Livre med = new Livre(titre,auteur);
				mediatheque.ajouter(med);
			}
			else if (type.equals("Article")) {
				Article med = new Article(titre,auteur);
				mediatheque.ajouter(med);
			}
			else System.out.println("probleme sur le titre (desole tu vas devoir redonner le titre et l'auteur)");
			
			System.out.println("As tu fini d'ajouter des mediums? oui ou non");
			String rep=sc.next();
			if (rep.equals("oui")) break;
			
		}
	}
}
