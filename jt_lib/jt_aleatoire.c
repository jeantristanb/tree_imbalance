#include "./jt_aleatoire.h"
/*=========================================================================
  NAME:
    d_util implementation

  DESCRIPTION:


=========================================================================*/

#define _d_util__implementation_


/*=======================================================================*/
#include <time.h>

/*-----------------------------------------------------------------------*/


/*=========================================================================
  Memory managment functions
=========================================================================*/
#undef D_MEM_TRACE

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  d_malloc
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
d_ptr d_malloc(d_size  siz1){
	d_ptr  ptr0;

	if (siz1 == 0) {
		return d_null;
	}

	ptr0 = (d_ptr)malloc(siz1);
	if (ptr0 == d_null) {
		d_error("could not allocate");
	}

#ifdef D_MEM_TRACE
	(void)fprintf(stderr, "%p\t+1\n", ptr0);	
#endif

	return ptr0;
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
d_ptr d_realloc(d_ptr ptr1, d_size  siz1){
	d_ptr  ptr0;

	if (siz1 == 0) {
		d_free(ptr1);

#ifdef D_MEM_TRACE
	(void)fprintf(stderr, "%p\t-1\n", ptr1);	
#endif

		return d_null;
	}

	if (ptr1 == d_null) {
		ptr0 = (d_ptr)malloc(siz1);

#ifdef D_MEM_TRACE
	(void)fprintf(stderr, "%p\t+1\n", ptr0);	
#endif

	} else {
		ptr0 = (d_ptr)realloc(ptr1, siz1);

#ifdef D_MEM_TRACE
	(void)fprintf(stderr, "%p\t-1\n", ptr1);	
	(void)fprintf(stderr, "%p\t+1\n", ptr0);	
#endif

	}

	if (ptr0 == d_null) {
		d_error("could not reallocate");
	}

	return ptr0;
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void d_free(d_ptr  ptr1){
	if (ptr1 != d_null) {
		(void)free(ptr1);

#ifdef D_MEM_TRACE
	(void)fprintf(stderr, "%p\t-1\n", ptr1);	
#endif

	}
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
d_ptr d_memmove(d_ptr   dst1, d_ptr   src1,d_size  siz1){
	return memmove(dst1, src1, siz1);
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
d_ptr d_memcpy(d_ptr   dst1,d_ptr   src1,d_size  siz1){
	return memcpy(dst1, src1, siz1);
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
d_ptr
d_memset(
	d_ptr   dst1,
	d_int   val1,
	d_size  siz1
){
	return memset(dst1, val1, siz1);
}



/*=========================================================================
  Error functions
=========================================================================*/

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void
d_error(
	d_char*  msg1
){
	(void)fprintf(stderr, "ERROR: %s\n", msg1);
	(void)fflush(stderr);
	exit(EXIT_FAILURE);
}




/*=========================================================================
  Random Generator [ran3]
=========================================================================*/

/*-------------------------------------------------------------------------
  Random state structure & type for [ran3]
-------------------------------------------------------------------------*/
typedef struct _d_random__ran3_state_  d_random__ran3_state;

struct _d_random__ran3_state_ {
	unsigned int  m_i;
	unsigned int  m_j;
	long int      m_v[56];
};
	
/*-------------------------------------------------------------------------
  Constants for [ran3]
-------------------------------------------------------------------------*/
#define d_random__ran3_BIG  1000000000
#define d_random__ran3_SEED  161803398


/*-------------------------------------------------------------------------
  Random functions for [ran3]
-------------------------------------------------------------------------*/

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
long int
d_random__ran3_get (
	void* sta1
){
	d_random__ran3_state*  s1 = (d_random__ran3_state*)(sta1);
	long int               v1;

	s1->m_i++;
	if (s1->m_i == 56) {
		s1->m_i = 1;
	}

	s1->m_j++;
	if (s1->m_j == 56) {
		s1->m_j = 1;
	}


	v1 = s1->m_v[s1->m_i]-s1->m_v[s1->m_j];

	if (v1 < 0) {
		v1+= d_random__ran3_BIG;
	}

	s1->m_v[s1->m_i] = v1;

	return v1;
}



/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
double
d_random__ran3_get_double(
	void* sta1
){
	return d_random__ran3_get(sta1)/(double)d_random__ran3_BIG ;
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void
d_random__ran3_set(
	void*     sta1,
	long int  see1
){
	d_random__ran3_state*  s1 = (d_random__ran3_state*)(sta1);
	unsigned int   i;
	unsigned int   j;
	long int       v1;
	long int       v2;

	if (see1 == 0) {
		see1 = 1;
	}

	v1 = d_abs(d_random__ran3_SEED-d_abs(see1));
	v1%= d_random__ran3_BIG;

	s1->m_v[0] = 0; 
	s1->m_v[55] = v1;

	v2 = 1;
	for (i = 1; i < 55; i++) {
		j = (21*i)%55;
		s1->m_v[j] = v2;
		v2 = v1-v2;
		if (v2 < 0) {
			v2+= d_random__ran3_BIG;
		}
		v1 = s1->m_v[j];
	}

	for (j = 0; j < 4; j++) {
		for (i = 1; i < 56; i++) {
			v1 = s1->m_v[i]-s1->m_v[1+(i+30)%55];
			if (v1 < 0) {
				v1+= d_random__ran3_BIG;
			}
			s1->m_v[i] = v1;
		}
	}

	s1->m_i = 0;
	s1->m_j = 31;

	return;
}

/*-------------------------------------------------------------------------
  State for [ran3]
-------------------------------------------------------------------------*/
static d_random__ran3_state  static__ran3_state;

/*-------------------------------------------------------------------------
  Random generator for [ran3]
-------------------------------------------------------------------------*/
static d_random  static__ran3 =
{
	d_random__ran3_set,
	d_random__ran3_get,
	d_random__ran3_get_double,
	&static__ran3_state
};




/*=========================================================================
  Generic random funtions for a random generator
=========================================================================*/

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Returns the random generator [nam1]
    N.B.: actually, only selects [ran3]
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
d_random*
d_random__select(
	char* nam1
){
	d_random*  rnd1;

	rnd1 = &static__ran3;
	d_random__default_seed(rnd1);

	return rnd1;
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Sets the seed for the random generator [rnd1]
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void
d_random__seed(
	d_random*  rnd1,
	long int   see1
){
	rnd1->m_set(rnd1->m_sta, see1);
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Sets a default seed for the random generator [rnd1]
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void
d_random__default_seed(
	d_random*  rnd1
){
	time_t  tim1;

	(void)time(&tim1);
	rnd1->m_set(rnd1->m_sta, tim1);
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Return an Uniform deviate on [0, 1[
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
double
d_random__unif(
	d_random* rnd1
){
	double x1;
	
	do {
		x1 = rnd1->m_get_double(rnd1->m_sta);
	} while (x1 == 1.0);
	
	if (x1 > 1.0) {
		d_error("random > 1.0");
	}
	return x1;
}
double gammln(double xx)
{
	double x, y, tmp, ser;
	static double cof[6]={76.18009172947146, -86.50532032941677, 24.01409824083091, -1.231739572450155, 0.1208650973866179e-2, -0.5395239384953e-5};
	int j;

	y = x = xx;
	tmp = x+5.5;
	tmp -= (x+0.5)*log(tmp);
	ser = 1.000000000190015;
	for (j = 0; j <= 5; j++)
		ser += cof[j]/++y;
	return(-tmp+log(2.5066282746310005*ser/x));
}

#define PI_POIDEV 3.141592654
/*loi de poisson inverse*/
double poisson_inverse(double xm)
{
	static double sq, alxm, g, oldm = (-1.0);
	double em, t, y;

	if (xm < 12.0) {
		if (xm != oldm) {
			oldm = xm;
			g = exp(-xm);
		}
		em = -1;
		t = 1.0;
		do {
			++em;
			t *= aleatoire();
		} while (t > g);
	} else {
		if (xm != oldm) {
			oldm = xm;
			sq = sqrt(2.0*xm);
			alxm = log(xm);
			g = xm*alxm-gammln(xm+1.0);
		}
		do {
			do {
				y = tan(PI_POIDEV*aleatoire());
				em = sq*y+xm;
			} while (em < 0.0);
			em = floor(em);
			t = 0.9*(1.0+y*y)*exp(em*alxm-gammln(em+1.0)-g);
		} while (aleatoire() > t);
	}
	return(em);
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Returns a Normal (mu=0, sigma=1) deviate
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
double
d_random__norm(
	d_random* rnd1
){
	double  x1;
	double  y1;
	double  r1;
	double  z1;

	do {
		x1 = -1.0+2.0*d_random__unif(rnd1);
		y1 = -1.0+2.0*d_random__unif(rnd1);
		r1 = x1*x1+y1*y1;
	} while ( (r1 > 1.0) || (r1 == 0.0) );

	z1 = y1*sqrt(-2.0*log(r1)/r1);

	return z1;
}
double aleatoire(){
    return d_random__unif(global__random);    
}
/*fonction reanvoyant un tableau de nb nombre aléatoire*/
int* TabIntAleatoire(int nb){
    int i,j, *t;
    t = i_allocate(nb);
    t[0] = 0;
    /* Tirage*/
    for (i = 1;i < nb; i++) {
        j = ((int)(aleatoire()*RAND_MAX))%i;
        t[i] = t[j];
        t[j] = i;
     }
 return t;
}


/*fonction reanvoyant un tableau de nb nombre aléatoire*/
int* TabIntAleatoireSansAllocation(int nb, int *t){
    int i,j;

    t[0] = 0;
    /* Tirage*/
    for (i = 1;i < nb; i++) {
        j = ((int)(aleatoire()*RAND_MAX))%i;
        t[i] = t[j];
        t[j] = i;
     }
 return t;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Returns an Exponential (lambda=1) deviate
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
double
d_random__expo(
	d_random* rnd1
){
	return -log(1.0-d_random__unif(rnd1));
}
double
d_random__expond(
	d_random* rnd1, double lambda
){
	return -log(1.0-d_random__unif(rnd1))/lambda;
}


double aleatoireExpo(double lambda){
       return (double)d_random__expond(global__random, lambda);      
}

void init_aleatoire(){
    global__random = d_random__select("");  
    /*d_random__seed(global__random, 5587975);*/
}

#define PI_BNLDEV 3.141592654

double bnldev(double pp, int n)
{
	int j;
	static int nold = (-1);
	double am, em, g, angle, p, bnl, sq, t, y;
	static double pold = (-1.0), pc, plog, pclog, en, oldg;

        if (pp==0)
            return 0.0;

	p = (pp <= 0.5 ? pp : 1.0-pp);
	am = n*p;
	if (n < 25) {
		bnl = 0.0;
		for (j = 1; j <= n; j++)
			if (aleatoire() < p) ++bnl;
	} else {
  	if (am < 1.0) {
			g = exp(-am);
			t = 1.0;
			for (j = 0; j <= n; j++) {
				t *= aleatoire();
				if (t < g)
        	break;
			}
			bnl = (j <= n ? j : n);
		} else {
			if (n != nold) {
				en = n;
				oldg = gammln(en+1.0);
				nold = n;
			}
			if (p != pold) {
				pc = 1.0-p;
				plog = log(p);
				pclog = log(pc);
				pold = p;
			}
			sq = sqrt(2.0*am*pc);
			do {
				do {
					angle = PI_BNLDEV*aleatoire();
					y = tan(angle);
					em = sq*y+am;
				} while ((em < 0.0) || (em >= (en+1.0)));
				em = floor(em);
				t = 1.2*sq*(1.0+y*y)*exp(oldg-gammln(em+1.0) -gammln(en-em+1.0)+em*plog+(en-em)*pclog);
			} while (aleatoire() > t);
			bnl = em;
		}
  }
	if (p != pp)
  	bnl = n-bnl;
	return(bnl);
}

/* 
 p = vecteur des probabilites (non cumule)
 Nel = nombre de SNP resultat
n = vecteur des SNP par fragments (resultat de la taille du noombre de fragment)
nb = nb de fragments (nombre de probabilite)
*/


void Multinomiale(int Nel, double *p, int nb, int *n)

{
  double *q;
  int i;
  /*Si il n'y a qu'une probabilite on la retourne*/
  if (nb==1)
    n[0]=Nel;
    
  else {
    if (p[nb-1]==1.0) {
      for (i=0;i<(nb-1);i++)
        n[i]=0;
      n[nb-1]=Nel;
    }
    else {
      q = (double *) malloc((nb-1)*sizeof(double));
      for (i=0;i<(nb-1);i++)
        q[i]=p[i]/(1-p[nb-1]);
      n[nb-1] = bnldev(p[nb-1],Nel);
      Multinomiale(Nel-n[nb-1],q,nb-1,n);
      free(q);
    }
  }
}

/* Tirage d'un element parmi n par dichotomie				*/
/* ------------------------------------------				*/
/* Un element i est caracterise par sa probabilite d'apparition p[i].	*/
/* Le tableau sp de n elements doit avoir la forme suivante :		*/
/*	i = 0..(n-1), sp[i] = Somme de j = 0..i des p[j]		*/
/* La dichotomie est un algo en log2 (n) : c'est a dire que la recherche*/
/* d'un element est realisee a l'issue de log2(n) comparaisons, alors	*/
/* qu'une recherche lineaire est realisee en moyenne a l'issue de n/2	*/
/* comparaisons.							*/
/* La dichotomie est d'autant plus interessante que n est grand.	*/

int Get_one (int    n, double sp[])
{
	int	i, n_2;
	double	rand;

	rand = aleatoire ();
	for (i=-1; n > 1;) {
		n_2 = n / 2;
		if (rand < sp[i+n_2]) {
			n = n_2;
		} else {
			i += n_2;
			n -= n_2;
		}
	}
	return (i+1);
}


double gamdev(int ia)

{

	int j;

	double am,e,s,v1,v2,x,y;



	if (ia < 1) erreur("Error in routine gamdev");

	if (ia < 6) {

		x=1.0;

		for (j=1;j<=ia;j++) x *=aleatoire();

		x = -log(x);

	} else {

		do {

			do {

				do {

					v1=aleatoire();

					v2=2.0*aleatoire()-1.0;

				} while (v1*v1+v2*v2 > 1.0);

				y=v2/v1;

				am=ia-1;

				s=sqrt(2.0*am+1.0);

				x=s*y+am;

			} while (x <= 0.0);

			e=(1.0+y*y)*exp(am*log(x/am)-s*y);

		} while (aleatoire() > e);

	}

	return x;

}
