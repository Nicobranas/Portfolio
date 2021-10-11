package BRANAS_Nicolas_TP3;
import java.util.ArrayList;

public class Mediatheque {
	
	private ArrayList<Medium> liste;
	
	public Mediatheque() {
		this.liste = new ArrayList<Medium>();
	}
	
	/**
	 * ajoute article a la liste
	 * @param medium
	 */
	public void ajouter (Medium medium) {
		
		this.liste.add(medium);
		
	}
	
	/**
	 * suprime un medium correspond au parametre
	 * @param titre
	 * @param auteur
	 */
	public void supprMedium(String titre, String auteur) {
		
		for (int i=0;i<this.liste.size();i++) {
			String a=this.liste.get(i).getAuteur();
			String t=this.liste.get(i).getTitre();
			if (a.equals(auteur) && t.equals(titre)) {
				this.liste.remove(i);
				System.out.println("Livre bien supprimé");
				break;
			}
		}	
		
	}
	
	/**
	 * suppr tout les articles d'un auteur
	 * @param auteur
	 */
	public void supprAuteur(String auteur) {
		
		for (int i=0;i<this.liste.size();i++) {
			String a=this.liste.get(i).getAuteur();
			if (a.equals(auteur) ){
				this.liste.remove(i);
				i--;
				//System.out.println("Livre bien supprimé");
			}
		}
		
	}
	
	/**
	 * liste tt les articles d'un auteur
	 * @param auteur
	 */
	public void lister(String auteur) {
		
		for (int i=0;i<this.liste.size();i++) {
			String a=this.liste.get(i).getAuteur();
			if (a.equals(auteur)) {
				this.liste.get(i).affiche();
			}
		}
		
	}
	
	/**
	 * liste le nbr de pret
	 * @return
	 */
	public int nbrPret() {
		
		int nbr=0;
		for (int i=0;i<this.liste.size();i++) {
			String nom=this.liste.get(i).getAmi();
			if (!nom.equals("Personne")){
				nbr++;
			}
		}
		return nbr;
		
	}

	/**
	 * getter pour les tests
	 * @return
	 */
	public ArrayList<Medium> getListe() {
		return liste;
	}
	

}
