
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int            m = 7, n, length= 127, k = 113, t = 2, d = 5;
//int           m, n, length, k, t, d;
//int           m = 6, n , length = 39, k = 27, t = 2, d = 5;
//int           m = 6, n , length = 45, k = 27, t = 3, d = 7;
//int           m = 8, n , length = 128, k = 27, t = 3, d = 7;
//int           m = 5, n , length = 31 , k = 21, t = 2, d = 5;
int             p[121];
int             alpha_to[1208], index_of[1208], g[1296];
int             recd[1208], data[1208], bb[1296];
int             seed;
int             numerr, errpos[1208], decerror = 0;
int             GetNo;


void read_p()
{
	int			i, ninf;

//	printf("\nEnter a value of m such that the code length is\n");
//	printf("2**(m-1) - 1 < length <= 2**m - 1\n\n");

    do {
//	   printf("Enter m (between 2 and 20): ");
//	   m = 6;//scanf("%d", &m);
     //  printf("%d", m);
	 //  printf("\n");
    } while ( !(m>1) || !(m<21) );
	for (i=1; i<m; i++)
		p[i] = 0;
	p[0] = p[m] = 1;
	if (m == 2)			p[1] = 1;
	else if (m == 3)	p[1] = 1;
	else if (m == 4)	p[1] = 1;
	else if (m == 5)	p[2] = 1;
	else if (m == 6)	p[1] = 1;
	else if (m == 7)	p[1] = 1;
	else if (m == 8)	p[4] = p[5] = p[6] = 1;
	else if (m == 9)	p[4] = 1;
	else if (m == 10)	p[3] = 1;
	else if (m == 11)	p[2] = 1;
	else if (m == 12)	p[3] = p[4] = p[7] = 1;
	else if (m == 13)	p[1] = p[3] = p[4] = 1;
	else if (m == 14)	p[1] = p[11] = p[12] = 1;
	else if (m == 15)	p[1] = 1;
	else if (m == 16)	p[2] = p[3] = p[5] = 1;
	else if (m == 17)	p[3] = 1;
	else if (m == 18)	p[7] = 1;
	else if (m == 19)	p[1] = p[5] = p[6] = 1;
	else if (m == 20)	p[3] = 1;
//	printf("p(x) = ");
    n = 1;
	for(i = 0; i <= m; i++) 
	{
        n *= 2;
	//	printf("%1d", p[i]);
	}
	//printf("\n");
	n = n / 2 - 1;
	ninf = (n + 1) / 2 - 1;
	do  {
		printf("Enter code length (%d < length <= %d): ", ninf, n);
	//	length = 36; //scanf("%d", &length);
    //   printf("%d", length);
	//    printf("\n");
	} while ( !((length <= n)&&(length>ninf)) );
}


void generate_gf()
{
	register int    i, mask;

	mask = 1;
	alpha_to[m] = 0;
	for (i = 0; i < m; i++) {
		alpha_to[i] = mask;
		index_of[alpha_to[i]] = i;
		if (p[i] != 0)
			alpha_to[m] ^= mask;
		mask <<= 1;
	}
	index_of[alpha_to[m]] = m;
	mask >>= 1;
	for (i = m + 1; i < n; i++) {
		if (alpha_to[i - 1] >= mask)
		  alpha_to[i] = alpha_to[m] ^ ((alpha_to[i - 1] ^ mask) << 1);
		else
		  alpha_to[i] = alpha_to[i - 1] << 1;
		index_of[alpha_to[i]] = i;
	}
	index_of[0] = -1;
}


void gen_poly()
{
	register int	ii, jj, ll, kaux;
	register int	test, aux, nocycles, root, noterms, rdncy;
	int             cycle[1024][21], size[1024], min[1024], zeros[1024];

	/* Generate cycle sets modulo n, n = 2**m - 1 */
	cycle[0][0] = 0;
	size[0] = 1;
	cycle[1][0] = 1;
	size[1] = 1;
	jj = 1;			/* cycle set index */
	if (m > 9) 
	{
//		printf("Computing cycle sets modulo %d\n", n);
//		printf("(This may take some time)...\n");
	}
	do {
		/* Generate the jj-th cycle set */
		ii = 0;
		do {
			ii++;
			cycle[jj][ii] = (cycle[jj][ii - 1] * 2) % n;
			size[jj]++;
			aux = (cycle[jj][ii] * 2) % n;
		} while (aux != cycle[jj][0]);
		
		/* Next cycle set representative */
		ll = 0;
		do {
			ll++;
			test = 0;
			for (ii = 1; ((ii <= jj) && (!test)); ii++)	
			/* Examine previous cycle sets */
			  for (kaux = 0; ((kaux < size[ii]) && (!test)); kaux++)
			     if (ll == cycle[ii][kaux])
			        test = 1;
		} while ((test) && (ll < (n - 1)));
		
		if (!(test))
		{
			jj++;	/* next cycle set index */
			cycle[jj][0] = ll;
			size[jj] = 1;
		}
	} while (ll < (n - 1));
	nocycles = jj;		/* number of cycle sets modulo n */

//	printf("Enter the error correcting capability, t: ");
//	scanf("%d", &t);
//	t= 2;
/////////////////////////////////


	d = 2 * t + 1;

	/* Search for roots 1, 2, ..., d-1 in cycle sets */
	kaux = 0;
	rdncy = 0;
	for (ii = 1; ii <= nocycles; ii++) {
		min[kaux] = 0;
		test = 0;
		for (jj = 0; ((jj < size[ii]) && (!test)); jj++)
			for (root = 1; ((root < d) && (!test)); root++)
				if (root == cycle[ii][jj])
				{
					test = 1;
					min[kaux] = ii;
				}
		if (min[kaux])
		{
			rdncy += size[min[kaux]];
			kaux++;
		}
	}

	noterms = kaux;
	kaux = 1;
	for (ii = 0; ii < noterms; ii++)
		for (jj = 0; jj < size[min[ii]]; jj++) 
		{
			zeros[kaux] = cycle[min[ii]][jj];
			kaux++;
		}

	k = length - rdncy;

    if (k < 0)
	{
         printf("Parameters invalid!\n");
		 AfxMessageBox("Parameters invalid!");
         exit(0);

	}

	CString str;
	str.Format("This is a (%d, %d, %d) binary BCH code\n", length, k, d);
	AfxMessageBox(str);

	printf("This is a (%d, %d, %d) binary BCH code\n", length, k, d);

	/* Compute the generator polynomial */
	g[0] = alpha_to[zeros[1]];
	g[1] = 1;		/* g(x) = (X + zeros[1]) initially */
	for (ii = 2; ii <= rdncy; ii++)
	{
	  g[ii] = 1;
	  for(jj = ii - 1; jj > 0; jj--)
	    if (g[jj] != 0)
	      g[jj] = g[jj - 1] ^ alpha_to[(index_of[g[jj]] + zeros[ii]) % n];
	    else
	      g[jj] = g[jj - 1];
	  g[0] = alpha_to[(index_of[g[0]] + zeros[ii]) % n];
	}

	printf("Generator polynomial:\ng(x) = ");
	for (ii = 0; ii <= rdncy; ii++) 
	{
	  printf("%d", g[ii]);
	  if (ii && ((ii % 50) == 0))
	    printf("\n");
	}

	GetNo = rdncy;//add by hgm
	printf("\n");
}


void Encode_Bch()
{
	register int    i, j;
	register int    feedback;

	for (i = 0; i < length - k; i++)
		bb[i] = 0;
	for (i = k - 1; i >= 0; i--)
	{
		feedback = data[i] ^ bb[length - k - 1];
		if (feedback != 0)
		{
			for (j = length - k - 1; j > 0; j--)
				if (g[j] != 0)
					bb[j] = bb[j - 1] ^ feedback;
				else
					bb[j] = bb[j - 1];
			bb[0] = g[0] && feedback;
		}
		else
		{
			for (j = length - k - 1; j > 0; j--)
				bb[j] = bb[j - 1];
			bb[0] = 0;
		}

	}

}


BOOL decode_bch()
{
	register int    i, j, u, q, t2, count = 0, syn_error = 0;
	int             elp[8][16], d[8], l[8], u_lu[8], s[8];
	int              loc[5], reg[5];
	t2            =     2 * t;

	/* first form the syndromes */
	
	CString              str;
	/*str.Format("n = %d",n);
							        
	//写入文本文件
	FILE *text;
	if((text = fopen("c:\\data.txt","a")) != NULL)
	{
		fputs(str + "\r\n",text);
		fclose(text);
	}*/


	for (i = 1; i <= t2; i++)
	{
		s[i] = 0;
		for (j = 0; j < length; j++)
			if (recd[j] != 0)
				s[i] ^= alpha_to[(i * j) % n];
		if (s[i] != 0)
			syn_error = 1; /* set error flag if non-zero syndrome */
		/* convert syndrome from polynomial form to index form  */
		s[i] = index_of[s[i]];
	
	}


	if (syn_error) 
	{	/* if there are errors, try to correct them */
		/* initialise table entries */
		d[0] = 0;			/* index form */
		d[1] = s[1];		/* index form */
		elp[0][0] = 0;		/* index form */
		elp[1][0] = 1;		/* polynomial form */

		for (i = 1; i < t2; i++) 
		{
			elp[0][i] = -1;	/* index form */
			elp[1][i] = 0;	/* polynomial form */
		}
		l[0] = 0;
		l[1] = 0;
		u_lu[0] = -1;
		u_lu[1] = 0;
		u = 0;
 
		do {
			u++;
			if (d[u] == -1) 
			{
				l[u + 1] = l[u];
				for (i = 0; i <= l[u]; i++) {
					elp[u + 1][i] = elp[u][i];
					elp[u][i] = index_of[elp[u][i]];
				}
			} 
			else
			{
				q = u - 1;
				while ((d[q] == -1) && (q > 0))
					q--;
				/* have found first non-zero d[q]  */
				if (q > 0) {
				  j = q;
				  do {
				    j--;
				    if ((d[j] != -1) && (u_lu[q] < u_lu[j]))
				      q = j;
				  } while (j > 0);
				}
 
				if (l[u] > l[q] + u - q)
					l[u + 1] = l[u];
				else
					l[u + 1] = l[q] + u - q;
 
				/* form new elp(x) */
				for (i = 0; i < t2; i++)
					elp[u + 1][i] = 0;
				for (i = 0; i <= l[q]; i++)
					if (elp[q][i] != -1)
						elp[u + 1][i + u - q] = 
                                   alpha_to[(d[u] + n - d[q] + elp[q][i]) % n];
				for (i = 0; i <= l[u]; i++) {
					elp[u + 1][i] ^= elp[u][i];
					elp[u][i] = index_of[elp[u][i]];
				}
			}
			u_lu[u + 1] = u - l[u + 1];
 
			/* form (u+1)th discrepancy */
			if (u < t2)
			{	
			  /* no discrepancy computed on last iteration */
			  if (s[u + 1] != -1)
			    d[u + 1] = alpha_to[s[u + 1]];
			  else
			    d[u + 1] = 0;
			    for (i = 1; i <= l[u + 1]; i++)
			      if ((s[u + 1 - i] != -1) && (elp[u + 1][i] != 0))
			        d[u + 1] ^= alpha_to[(s[u + 1 - i] 
			                      + index_of[elp[u + 1][i]]) % n];
			  /* put d[u+1] into index form */
			  d[u + 1] = index_of[d[u + 1]];	
			}
		} while ((u < t2) && (l[u + 1] <= t));
 
		u++;
		if (l[u] <= t)
		{
			/* Can correct errors */
			/* put elp into index form */
			for (i = 0; i <= l[u]; i++)
				elp[u][i] = index_of[elp[u][i]];

			/* Chien search: find roots of the error location polynomial */
			for (i = 1; i <= l[u]; i++)
				reg[i] = elp[u][i];
			count = 0;
			for (i = 1; i <= n; i++)
			{
				q = 1;

				for (j = 1; j <= l[u]; j++)
				{
					if (reg[j] != -1)
					{
						reg[j] = (reg[j] + j) % n;
						q ^= alpha_to[reg[j]];
					}
				}

				if (!q) 
				{	
				     // store root and error
					 // location number indices 
					loc[count] = n - i;
					count++;
				}
			}
		
			if (count == l[u])
			{

	            CString str,str1;
				str  =  str1 = "";
				str = "纠正位置:";
			
				for (i = 0; i < l[u]; i++)
				{
					recd[loc[i]] ^= 1;
				
					str1.Format(" %d",loc[i]);
					str = str + str1;
				}
				
			
				//str.Format("纠正位置：%d",loc[i]);
							        
				//写入文本文件
				FILE *text;
				if((text = fopen("c:\\data.txt","a")) != NULL)
				{
					fputs(str + "\r\n",text);
					fclose(text);
				}

				return TRUE;
			}
			else
			{
				str.Format("超出纠码范围");

				//写入文本文件
				FILE *text;
				if((text = fopen("c:\\data.txt","a")) != NULL)
				{
					fputs(str + "\r\n",text);
					fclose(text);
				}
				//
				return FALSE;
			}

		}
	}

	return TRUE;
}


BOOL decode63453()
{
	
	CString str;
	register int    i, j, u, q, t2, count = 0, syn_error = 0;
	int     elp[8][6], d[7], l[8], u_lu[8], s[7];
	long      temph,templ,temph_b,templ_b;
	t2 = 2 * t;

	
    temph = 0;
	templ = 0;
	for(i = 0;i <= 31;i ++)
	{  
		temph_b = temph_b<<1;
		if(recd[i] != 0)
		{
			temph_b = temph_b|0x01;
		}
		
	}
	
	for(i = 32;i <= 63;i ++)
	{   
		templ_b=templ_b<<1;
		if(recd[i] != 0)
		{
			templ_b=templ_b|0x01;
		}
		
	}
	/* first form the syndromes */
	
	for (i = 1; i <= t2; i++) 
	{
		s[i] = 0;
		
		temph = temph_b; 
		templ = templ_b; 
	
		for(j = 0;j <= 31;j++)
		{  
			if((temph&0x80000000)!= 0)
			{
				s[i] ^= alpha_to[(i * j) % n];
			}
			temph = temph<<1;
		}

  	     for(j = 32;j < 63;j ++)
		 {  
			 if((templ&0x80000000)!= 0)
			 {
				 s[i] ^= alpha_to[(i * j) % n];
			 }
			 templ=templ<<1;
			 
		 }
		 
		 //-----
		 if (s[i] != 0)
		 {
			 syn_error = 1;
		 }
		 
		 s[i] = index_of[s[i]];
		 
	}
	
	
	if (syn_error)
	{	/* if there are errors, try to correct them */
		/* initialise table entries */
		d[0] = 0;			/* index form */
		d[1] = s[1];		/* index form */
		elp[0][0] = 0;		/* index form */
		elp[1][0] = 1;		/* polynomial form */

		for (i = 1; i < t2; i++)
		{
			elp[0][i] = -1;	/* index form */
			elp[1][i] = 0;	/* polynomial form */
		}
		l[0] = 0;
		l[1] = 0;
		u_lu[0] = -1;
		u_lu[1] = 0;
		u = 0;
		
		do {
			u++;
			if (d[u] == -1) {
				l[u + 1] = l[u];
				for (i = 0; i <= l[u]; i++) {
					elp[u + 1][i] = elp[u][i];
					elp[u][i] = index_of[elp[u][i]];
				}
			} else
				
			{
				q = u - 1;
				while ((d[q] == -1) && (q > 0))
					q--;
				/* have found first non-zero d[q]  */
				if (q > 0) {
					j = q;
					do {
						j--;
						if ((d[j] != -1) && (u_lu[q] < u_lu[j]))
							q = j;
					} while (j > 0);
				}
				
				if (l[u] > l[q] + u - q)
					l[u + 1] = l[u];
				else
					l[u + 1] = l[q] + u - q;
				
				/* form new elp(x) */
				for (i = 0; i < t2; i++)
					elp[u + 1][i] = 0;
				for (i = 0; i <= l[q]; i++)
					if (elp[q][i] != -1)
						elp[u + 1][i + u - q] = 
						alpha_to[(d[u] + n - d[q] + elp[q][i]) % n];
					for (i = 0; i <= l[u]; i++) {
						elp[u + 1][i] ^= elp[u][i];
						elp[u][i] = index_of[elp[u][i]];
					}
			}
			u_lu[u + 1] = u - l[u + 1];
			
			/* form (u+1)th discrepancy */
			if (u < t2) {	
				/* no discrepancy computed on last iteration */
				if (s[u + 1] != -1)
					d[u + 1] = alpha_to[s[u + 1]];
				else
					d[u + 1] = 0;
				for (i = 1; i <= l[u + 1]; i++)
					if ((s[u + 1 - i] != -1) && (elp[u + 1][i] != 0))
						d[u + 1] ^= alpha_to[(s[u + 1 - i] 
						+ index_of[elp[u + 1][i]]) % n];
					/* put d[u+1] into index form */
					d[u + 1] = index_of[d[u + 1]];	
			}
		} while ((u < t2) && (l[u + 1] <= t));
		
		u++;
		if (l[u] <= t) {/* Can correct errors */
			/* put elp into index form */
			for (i = 0; i <= l[u]; i++)
				elp[u][i] = index_of[elp[u][i]];
			
			
			
			/* Chien search: find roots of the error location polynomial */
			for (i = 1; i <= l[u]; i++)
				s[i] = elp[u][i];
			count = 0;
			for (i = 1; i <= n; i++) {
				q = 1;
				for (j = 1; j <= l[u]; j++)
					if (s[j] != -1) {
						s[j] = (s[j] + j) % n;
						q ^= alpha_to[s[j]];
					}
					if (!q) {	/* store root and error
						* location number indices */
						d[count] = n - i;
						count++;
						
					}
			}
			
			if (count == l[u])	
				for (i = 0; i < l[u]; i++)
				{	
					//recd[d[i]] ^= 1;

					str.Format("纠正位置：%d",d[i]);
							        
					//写入文本文件
					FILE *text;
					if((text = fopen("c:\\data.txt","a")) != NULL)
					{
						fputs(str + "\r\n",text);
						fclose(text);
					}

					for(j = 0;j <= 63;j ++)
					{
						temph=temph<<1;
						if((templ&0x80000000)==0x80000000)
							temph=temph|0x01;
						
						templ=templ<<1;
						if((temph_b&0x80000000)==0x80000000)
							templ=templ|0x01;
						
						temph_b=temph_b<<1;
						if((templ_b&0x80000000)==0x80000000)
							temph_b=temph_b|0x01;
						
						templ_b=templ_b<<1;
						if(j==d[i])
						{templ=templ^0x01;}
						
						// temph,templ,temph_b,templ_b;
					}
					temph_b=temph;
					templ_b=templ;
				}
				
				for(i = 0;i <= 31; i ++)
				{   
					if((temph_b&0x80000000)==0)
					{
						recd[i]=0;
					}
					else
					{
						recd[i]=1;
					}
					temph_b=temph_b<<1;
				}
				
				for(i = 32;i < 63; i++)
				{   
					if((templ_b&0x80000000)==0)
					{
						recd[i]=0;
					}
					else
					{
						recd[i]=1;
					}
					templ_b=templ_b<<1;
				}
				
		}
		return TRUE;

	}
	return FALSE;


	/*
	register int    i, j, u, q, t2, count = 0, syn_error = 0;
	int             elp[8][16], d[8], l[8], u_lu[8], s[8];
	int              loc[5], reg[5];
	t2 = 2 * t;

	// first form the syndromes 

	for (i = 1; i <= t2; i++)
	{
		s[i] = 0;
		for (j = 0; j < length; j++)
			if (recd[j] != 0)
				s[i] ^= alpha_to[(i * j) % n];
		if (s[i] != 0)
			syn_error = 1; // set error flag if non-zero syndrome 
		// convert syndrome from polynomial form to index form  
		s[i] = index_of[s[i]];
	
	}


	if (syn_error) 
	{
		// if there are errors, try to correct them 
		// initialise table entries 
		d[0] = 0;			// index form
		d[1] = s[1];		// index form 
		elp[0][0] = 0;		// index form 
		elp[1][0] = 1;		// polynomial form 

		for (i = 1; i < t2; i++) 
		{
			elp[0][i] = -1;	// index form 
			elp[1][i] = 0;	// polynomial form 
		}

		l[0] = 0;
		l[1] = 0;
		u_lu[0] = -1;
		u_lu[1] = 0;
		u = 0;
 
		do {
			u++;
			if (d[u] == -1) 
			{
				l[u + 1] = l[u];
				for (i = 0; i <= l[u]; i++) {
					elp[u + 1][i] = elp[u][i];
					elp[u][i] = index_of[elp[u][i]];
				}
			} 
			else
			{
				q = u - 1;
				while ((d[q] == -1) && (q > 0))
					q--;
				// have found first non-zero d[q]  
				if (q > 0) {
				  j = q;
				  do {
				    j--;
				    if ((d[j] != -1) && (u_lu[q] < u_lu[j]))
				      q = j;
				  } while (j > 0);
				}
 
				if (l[u] > l[q] + u - q)
					l[u + 1] = l[u];
				else
					l[u + 1] = l[q] + u - q;
 
				// form new elp(x) 
				for (i = 0; i < t2; i++)
					elp[u + 1][i] = 0;
				for (i = 0; i <= l[q]; i++)
					if (elp[q][i] != -1)
						elp[u + 1][i + u - q] = 
                                   alpha_to[(d[u] + n - d[q] + elp[q][i]) % n];
				for (i = 0; i <= l[u]; i++) {
					elp[u + 1][i] ^= elp[u][i];
					elp[u][i] = index_of[elp[u][i]];
				}
			}
			u_lu[u + 1] = u - l[u + 1];
 
			// form (u+1)th discrepancy 
			if (u < t2)
			{	
			  // no discrepancy computed on last iteration 
			  if (s[u + 1] != -1)
			    d[u + 1] = alpha_to[s[u + 1]];
			  else
			    d[u + 1] = 0;
			    for (i = 1; i <= l[u + 1]; i++)
			      if ((s[u + 1 - i] != -1) && (elp[u + 1][i] != 0))
			        d[u + 1] ^= alpha_to[(s[u + 1 - i] 
			                      + index_of[elp[u + 1][i]]) % n];
			  // put d[u+1] into index form 
			  d[u + 1] = index_of[d[u + 1]];	
			}
		} while ((u < t2) && (l[u + 1] <= t));
 
		u++;
		if (l[u] <= t)
		{
			// Can correct errors 
			// put elp into index form 
			for (i = 0; i <= l[u]; i++)
				elp[u][i] = index_of[elp[u][i]];

			// Chien search: find roots of the error location polynomial 
			for (i = 1; i <= l[u]; i++)
				reg[i] = elp[u][i];
			count = 0;
			for (i = 1; i <= n; i++)
			{
				q = 1;

				for (j = 1; j <= l[u]; j++)
				{
					if (reg[j] != -1)
					{
						reg[j] = (reg[j] + j) % n;
						q ^= alpha_to[reg[j]];
					}
				}

				if (!q) 
				{	
				     // store root and error
					 // location number indices 
					loc[count] = n - i;
					count++;
				}
			}
		
			if (count == l[u])
			{
				for (i = 0; i < l[u]; i++)
				{
					recd[loc[i]] ^= 1;
					CString str;
					str.Format("纠正位置：%d",loc[i]);
							        
					//写入文本文件
					FILE *text;
					if((text = fopen("c:\\data.txt","a")) != NULL)
					{
						fputs(str + "\r\n",text);
						fclose(text);
					}
					//
				}
			}
			else
			{
				return FALSE;
			}
		}
		else
		{
			return FALSE;
		}

	}
	return TRUE;
	*/
}



