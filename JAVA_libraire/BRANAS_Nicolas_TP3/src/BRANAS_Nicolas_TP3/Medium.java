package BRANAS_Nicolas_TP3;

public abstract class Medium {

	protected String titre;
	protected String auteur;
	protected String date;
	protected String ami;
	
	/**
	 * constructeur, ami different de personne si le medium est prete
	 * @param titre
	 * @param auteur
	 */
	public Medium(String titre, String auteur) {
		
		this.titre=titre;
		this.auteur=auteur;
		this.ami="Personne";
		
	}
	
	/**
	 * affichage
	 */
	public void affiche() {
		System.out.println(this.titre+" "+this.auteur+" "+this.date+" ");
	}

	public String getTitre() {
		return titre;
	}

	public void setTitre(String titre) {
		this.titre = titre;
	}

	public String getAuteur() {
		return auteur;
	}

	public void setAuteur(String auteur) {
		this.auteur = auteur;
	}

	/**
	 * important car permet de savoir si prete
	 * @return
	 */
	public String getAmi() {
		return ami;
	}

	/**
	 * permet de prete
	 * @param ami
	 */
	public void setAmi(String ami) {
		this.ami = ami;
	}
	
	
	
}
