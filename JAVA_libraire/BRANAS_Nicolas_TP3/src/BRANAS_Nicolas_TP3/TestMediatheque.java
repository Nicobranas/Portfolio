package BRANAS_Nicolas_TP3;

import static org.junit.Assert.*;

import org.junit.Test;

public class TestMediatheque {

	
	DVD a = new DVD("homme elastique","alex");
	CD b = new CD("homme de pierre","theau");
	
	Mediatheque med = new Mediatheque();
	
	@Test
	public void testAjouter() {
		med.ajouter(a);
		med.ajouter(b);
		assertEquals(2,med.getListe().size());
	}
	
	@Test
	public void testSupprMedium() {
		med.ajouter(b);
		med.supprMedium("homme de pierre","theau");
		assertEquals(0,med.getListe().size());
	}
	
	@Test
	public void testSupprAuteur() {
		med.ajouter(a);
		med.ajouter(b);
		med.supprAuteur("theau");
		assertEquals(1,med.getListe().size());
	}
	
	@Test
	public void testLister() {
	med.ajouter(a);
	med.ajouter(b);
	med.lister("theau");
	}
	
	@Test
	public void tesNbrPret() {
		
		med.ajouter(a);
		a.setAmi("hocine");
		int test=med.nbrPret();
		assertEquals(1,test);
		
	}
	
}
