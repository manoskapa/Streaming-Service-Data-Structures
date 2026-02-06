/*****************************************************
 * @file   Movie.c                                   *
 * @author Paterakis Giorgos <geopat@csd.uoc.gr>     *
 *                                                   *
 * @brief Implementation for Movie.h 				 *
 * Project: Winter 2023						         *
 *****************************************************/
#include "Movie.h"

/** 
 * @brief Creates a new user.
 * Creates a new user wi th userID as its identification.
 *
 * @param userID The new user's identification
 *
 * @return 0 on success
 *         1 on failureee
 */
int hashfun(unsigned int userID)
{
	return userID % hashtable_size;
}
int register_user(unsigned int userID)
{
	int i;
	i = hashfun(userID);
	user_t *tmp = user_hashtable_p[i], *prev = NULL;
	if (user_hashtable_p[i] == NULL)
	{
		struct user *newu = malloc(sizeof(struct user));
		if (newu == NULL)
		{
			return 0; // failure
		}
		newu->userID = userID;
		newu->history = NULL;
		newu->next = NULL;
		user_hashtable_p[i] = newu;
		printU(i);
		return 1;
	}

	while (tmp)
	{
		if (tmp->userID == userID)
		{
			return 0;
		}
		prev = tmp;
		tmp = tmp->next;
	}
	struct user *newu = malloc(sizeof(struct user));
	newu->userID = userID;
	newu->history = NULL;
	newu->next = NULL;
	prev->next = newu;
	printf("R <%d>\n", userID);
	printU(i);
	return 1;
}
void printU(int i)
{
	user_t *tmp = user_hashtable_p[i];
	printf("Chain <%d> of Users:\n", i);
	while (tmp)
	{
		printf("<%d>\n", tmp->userID);
		tmp = tmp->next;
	}
	printf("DONE\n");
}
/**
 * @brief Deletes a user.
 * Deletes a user with userID from the system, along with users' history tree.
 *
 * @param userID The new user's identification
 *
 * @return 0 on success
 *         1 on failure
 */

int unregister_user(unsigned int userID)
{

	user_t *prev = NULL;
	int i = hashfun(userID);
	user_t *tmp = user_hashtable_p[i];

	printf("U <%d>\n", userID);
	if (user_hashtable_p[i] == NULL)
	{
		return 0;
	}

	if (user_hashtable_p[i]->userID == userID)
	{
		user_hashtable_p[i] = user_hashtable_p[i]->next;
		printU(i);
		return 1;
	}

	while (tmp && tmp->userID != userID)
	{

		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp != NULL)
	{
		prev->next = tmp->next;
	}
	printU(i);
	return 1;
}

/**
 * @brief Add new movie to new release binary tree.
 * Create a node movie and insert it in 'new release' binary tree.
 *
 * @param movieID The new movie identifier
 * @param category The category of the movie
 * @param year The year movie released
 *
 * @return 0 on success
 *         1 on failure
 */

int add_new_movie(unsigned int movieID, int category, int year)
{
	struct movie *tmp = malloc(sizeof(struct movie));
	struct movie *root = NULL, *father = NULL;
	printf("\nA <%d><%d><%d>\n", movieID, category, year);
	if (tmp == NULL)
	{
		return 0;
	}
	tmp->movieID = movieID;
	tmp->category = category;
	tmp->year = year;
	tmp->watchedCounter = 0;
	tmp->sumScore = 0;
	tmp->lc = NULL;
	tmp->rc = NULL;
	if (new_releases == NULL)
	{
		new_releases = tmp;
	}
	else
	{
		root = new_releases;

		while (root)
		{
			if (root->movieID > tmp->movieID)
			{
				father = root;
				root = root->lc;
			}
			else if (root->movieID < tmp->movieID)
			{
				father = root;
				root = root->rc;
			}
			else
			{
				return 0; // there already is a movie with that id
			}
		}
		if (tmp->movieID > father->movieID)
		{
			father->rc = tmp;
		}
		else
		{
			father->lc = tmp;
		}
	}
	printf("New releases Tree:\n");
	inorder(new_releases);
	printf("\nDONE\n");
	return 1;
}
/*Α <movieID> <category> <year>
New releases Tree:
<new_releases>: <movieID1>, ... , < movieIDn>
DONE
*/
extern movie_t *centinel;
void inorder(struct movie *tmp)
{

	if (tmp == NULL)
	{
		return;
	}
	inorder(tmp->lc);
	printf("<%d>,", tmp->movieID);
	inorder(tmp->rc);
}
void inorder_centinel(struct movie *tmp)
{

	if (tmp == centinel)
	{
		return;
	}
	inorder_centinel(tmp->lc);
	printf("<%d>,", tmp->movieID);
	inorder_centinel(tmp->rc);
}

struct movie *m0[100];
int m0i = 0;
struct movie *m1[100];
int m1i = 0;

struct movie *m2[100];
int m2i = 0;
int m3i = 0;
int m4i = 0;
int m5i = 0;
struct movie *m3[100];
struct movie *m4[100];
struct movie *m5[100];

void inorderD(struct movie *tmp)
{

	if (tmp == NULL)
	{
		return;
	}
	inorderD(tmp->lc);
	if (tmp->category == 0)
	{
		m0[m0i] = tmp;
		m0i++;
	}
	else if (tmp->category == 1)
	{
		m1[m1i] = tmp;
		m1i++;
	}
	else if (tmp->category == 2)
	{
		m2[m2i] = tmp;
		m2i++;
	}
	else if (tmp->category == 3)
	{
		m3[m3i] = tmp;
		m3i++;
	}
	else if (tmp->category == 4)
	{
		m4[m4i] = tmp;
		m4i++;
	}
	else
	{
		m5[m5i] = tmp;
		m5i++;
	}
	inorderD(tmp->rc);
}

extern movie_t *centinel;
struct movie *maketreeT(struct movie *arr[100], int start, int end)
{

	int mid;

	if (start > end)
	{
		return centinel;
	}

	struct movie *tmp = malloc(sizeof(struct movie));
	mid = (start + end) / 2;

	*(tmp) = *(arr[mid]);
	
	// tmp->movieID = arr[mid]->movieID;

	tmp->lc = maketreeT(arr, start, mid - 1);
	tmp->rc = maketreeT(arr, mid + 1, end);
	return tmp;
}

/**
 * @brief Distribute the movies from new release binary tree to the array of categories.
 *
 * @return 0 on success
 *         1 on failure
 */
/*Movie Category Array:
<category0>: <movieID0
1>, ... , < movieID0
n0>
<category1>: <movieID1
1>, ... , < movieID1
n1>
...
<category5>: <movieID5
1>, ... , < movieID5
4>
DONE
*/
int distribute_movies(void)
{

	printf("D\n");
	printf("Movie Category Array:\n");

	inorderD(new_releases);

	printf("<category0>: ");
	categoryArray[0]->movie = maketreeT(m0, 0, m0i - 1);
	inorder_centinel(categoryArray[0]->movie);

	printf("\n<category1>: ");
	categoryArray[1]->movie = maketreeT(m1, 0, m1i - 1);
	inorder_centinel(categoryArray[1]->movie);

	printf("\n<category2>: ");
	categoryArray[2]->movie = maketreeT(m2, 0, m2i - 1);
	inorder_centinel(categoryArray[2]->movie);

	printf("\n<category3>: ");
	categoryArray[3]->movie = maketreeT(m3, 0, m3i - 1);
	inorder_centinel(categoryArray[3]->movie);

	printf("\n<category4>: ");
	categoryArray[4]->movie = maketreeT(m4, 0, m4i - 1);
	inorder_centinel(categoryArray[4]->movie);

	printf("\n<category5>: ");
	categoryArray[5]->movie = maketreeT(m5, 0, m5i - 1);
	inorder_centinel(categoryArray[5]->movie);
	printf("\nDONE");

	return 1;
}

/**
 * @brief User rates the movie with identification movieID with score
 *
 * @param userID The identifier of the user
 * @param category The Category of the movie
 * @param movieID The identifier of the movie
 * @param score The score that user rates the movie with id movieID
 *
 * @return 0 on success
 *         1 on failure
 */

int watch_movie(unsigned int category, unsigned int userID, unsigned int movieID, int score)
{
	struct movie *tmp = categoryArray[category]->movie;

	printf("\nW<%d><%d><%d><%d>\n", userID, category, movieID, score);
	printf("History Tree of user <userID>\n", userID);
	centinel->movieID=movieID;
	while (tmp->movieID!=movieID)
	{
		if (tmp->movieID > movieID)
		{
			tmp = tmp->lc;
		}
		else if (tmp->movieID < movieID)
		{
			tmp = tmp->rc;
		}
		
	}
	if (tmp == centinel)
	{
		return 0;
	}
	else{
		tmp->watchedCounter = tmp->watchedCounter + 1;
			tmp->sumScore = tmp->sumScore + score;
	}
	// asumes that we have found such movie in the category

	int i = hashfun(userID);

	user_t *nuser = NULL, *curr = user_hashtable_p[i];
	while (curr)
	{
		if (curr->userID == userID)
		{
			nuser = curr;
			break;
		}
		else
		{
			curr = curr->next;
		}
	}

	if (curr == NULL)
	{
		return 0;
	}

	if (nuser->history == NULL)
	{
		userMovie_t *newum = malloc(sizeof(userMovie_t));
		if (newum == NULL)
		{
			return 0;
		}

		newum->movieID = movieID;
		newum->score = score;
		newum->category = category;

		newum->parent = NULL;
		newum->lc = NULL;
		newum->rc = NULL;

		nuser->history = newum;
	}
	else
	{
		nuser->history = insertkey(nuser->history, movieID, category, score);
	}

	inorderW(nuser->history);

	printf("DONE\n");
	return 1;
}
void inorderW(userMovie_t *tmp)
{

	if (tmp == NULL)
	{
		return;
	}
	inorderW(tmp->lc);
	printf("<%d,%d>\n", tmp->movieID, tmp->score);
	inorderW(tmp->rc);
}

userMovie_t *insertkey(userMovie_t *root, int key, int category, int score)
{
	userMovie_t *tmp = root, *father = NULL;

	while (tmp)
	{
		father = tmp;
		if (tmp->movieID > key)
		{
			tmp = tmp->lc;
		}
		else if (tmp->movieID < key)
		{
			tmp = tmp->rc;
		}
		else
		{
			if (tmp->lc == NULL && tmp->rc == NULL)
			{
				return root; // do nothing
			}
			tmp = tmp->lc;
		}
	}

	userMovie_t *newnodeL = malloc(sizeof(userMovie_t));
	userMovie_t *newnodeR = malloc(sizeof(userMovie_t));

	if (father->movieID > key)
	{
		newnodeL->movieID = key;
		newnodeL->category = category;
		newnodeL->score = score;
		newnodeL->parent = father;
		newnodeL->lc = NULL;
		newnodeL->rc = NULL;

		newnodeR->movieID = father->movieID;
		newnodeR->category = father->category;
		newnodeR->score = father->score;
		newnodeR->parent = father;
		newnodeR->lc = NULL;
		newnodeR->rc = NULL;

		father->movieID = key;
		father->category = category;
		father->score = score;

		father->lc = newnodeL;
		father->rc = newnodeR;
	}
	else
	{
		newnodeR->movieID = key;
		newnodeR->category = category;
		newnodeR->score = score;
		newnodeR->parent = father;
		newnodeR->lc = NULL;
		newnodeR->rc = NULL;

		newnodeL->movieID = father->movieID;
		newnodeL->category = father->category;
		newnodeL->score = father->score;
		newnodeL->parent = father;
		newnodeL->lc = NULL;
		newnodeL->rc = NULL;

		father->lc = newnodeL;
		father->rc = newnodeR;
	}

	return root;
}

/**
 * @brief Identify the best rating score movie and cluster all the movies of a category.
 *
 * @param userID The identifier of the user
 * @param score The minimum score of a movie
 *
 * @return 0 on success
 *         1 on failure
 */

int filter_movies(unsigned int userID, unsigned int score)
{
	int i, ttscore=0;
	printf("F <%d><%d>\n  ", userID, score);
	for (i = 0; i <= 5; i++)
	{
		ttscore += inorderF(categoryArray[i]->movie, score); // 5,score???
	//	printf("\n%d %d\n",i,ttscore);
	}

	movie_t **array = (movie_t **)malloc(ttscore * sizeof(movie_t *));
	int j = 0;
	for (i = 0; i <= 5; i++)
	{

		inorderFARR(categoryArray[i]->movie, score, array, &j);
	}	
	//printf("ttscore:%d",ttscore);
	heap_sort(array,ttscore);
	for (int k = 0; k < ttscore; k++)
	{
		float z = (float)array[k]->sumScore / (float)array[k]->watchedCounter;
		printf("<%d><%f>, ", array[k]->movieID, z);
	}
	printf("\nDONE\n");

	return 1;
}

int left_child(int i,int ttscore)
{
	int k = 2 * i -ttscore;
	return k;
}

int right_child(int i,int ttscore)
{
	int k = 2 * i -ttscore-1;
	return k;
}
void heapify(movie_t **A, int i, int j,int ttscore)
{

	int m = j;
	int p;

	while ((left_child(m,ttscore) >= i && ((float)A[left_child(m,ttscore)]->sumScore/ (float)A[left_child(m,ttscore)]->watchedCounter)< ((float)A[m]->sumScore/(float)A[m]->watchedCounter) )||
		   (right_child(m,ttscore) >= i &&((float) A[right_child(m,ttscore)]->sumScore/ (float)A[right_child(m,ttscore)]->watchedCounter )<((float)A[m]->sumScore/(float)A[m]->watchedCounter)))
	{
		if (right_child(m,ttscore) >= i)
		{
			if ((float)A[left_child(m,ttscore)]->sumScore/(float) A[left_child(m,ttscore)]->watchedCounter< (float)A[right_child(m,ttscore)]->sumScore/ (float)A[right_child(m,ttscore)]->watchedCounter)
			{
				p = left_child(m,ttscore);
			}
			else
			{
				p = right_child(m,ttscore);
			}
		}
		else
		{
			p = i;
		}

		// Swap A[m] and A[p]
		swap(&A[m], &A[p]);
		m = p;
	}
}
void swap(movie_t **a, movie_t **b)
{
	movie_t *temp = *a;
	*a = *b;
	*b = temp;
}

void heap_sort(movie_t **A, int n)
{
	// initialize heap
	for (int k = 1; k < n; k++)
	{
		heapify(A, 0, k,n);
	}
	for (int i = 0; i < n - 1; i++)
	{
		swap(&A[i], &A[n - 1]);
		heapify(A, i + 1, n - 1,n);
	}
}

void inorderFARR(struct movie *tmp, int score, movie_t **array, int *j)
{

	if (tmp != centinel)
	{

		inorderFARR(tmp->lc, score, array, j);

		if (tmp->watchedCounter > 0 && (tmp->sumScore / tmp->watchedCounter) >= score)
		{
			array[*j] = tmp;

			//printf("\nARRAF id= %d sumscore=%d\n", array[j]->movieID, array[j]->sumScore);
			(*j)++;
		}

		inorderFARR(tmp->rc, score, array, j);
	}
}
int inorderF(struct movie *tmp, int score)
{
	int lc = 0;
	int rc = 0;
	int tmp1 = 0;

	if (tmp == centinel)
	{
		return 0;
	}

	lc = inorderF(tmp->lc, score);

	if (tmp->watchedCounter != 0 && (tmp->sumScore / tmp->watchedCounter) >= score)
	{
		tmp1 = 1;
	}

	rc = inorderF(tmp->rc, score);

	return lc + rc + tmp1;
}

/**
 * @brief Find movies from categories withn median_score >= score t
 *
 * @param userID The identifier of the user
 * @param category Array with the categories to search.
 * @param score The minimum score the movies we want to have
 *
 * @return 0 on success
 *         1 on failure
 */

userMovie_t *FindNextLeaf(userMovie_t *prevleaf)
{
	// first time!
	userMovie_t *curr = NULL;

	if(prevleaf->parent==NULL){
		return NULL;
	}
	if (prevleaf->parent->rc == NULL)
	{
		return NULL;
	}

	else if (prevleaf->parent->rc != prevleaf)
	{
		prevleaf=prevleaf->parent->rc;
		while (prevleaf->lc != NULL)
			{
				prevleaf = prevleaf->lc;
			}
		return prevleaf;
	}
	
		curr = prevleaf->parent;
		
			while (prevleaf == curr->rc)
			{
				if(curr->parent==NULL){
					return NULL;
				}
				
				prevleaf = curr;
				curr = curr->parent;
			}
			
			prevleaf = curr->rc;
			
			while (prevleaf->lc != NULL)
			{
				prevleaf = prevleaf->lc;
			}

			return prevleaf;
}
		
	


int user_stats(unsigned int userID)
{
	printf("Q <%d>\n", userID);
	int i = hashfun(userID);
	user_t *nuser = NULL, *curr = user_hashtable_p[i];
	userMovie_t *find1leaf = NULL;

	while (curr)
	{
		if (curr->userID == userID)
		{
			nuser = curr;
			break;
		}
		else
		{
			curr = curr->next;
		}
	}

	if (curr == NULL)
	{
		return 0;
	}

	if (nuser->history != NULL)
	{
		userMovie_t *find1leaf = NULL;
		find1leaf = nuser->history;
		while (find1leaf->lc != NULL)
		{
			find1leaf = find1leaf->lc;
			
		}
		int score = find1leaf->score;
		int counter = 1;

		//printf("movie id %d,counter %d score %d\n", find1leaf->movieID, counter, score);
		while (find1leaf != NULL)
		{
			userMovie_t *newleaf=FindNextLeaf(find1leaf);
			find1leaf=newleaf;
			
			//if(find1leaf->parent==nuser->history&&nuser->history->rc==find1leaf);
			if (find1leaf != NULL)
			{
				score += find1leaf->score;
				counter++;
				//printf("<%f>\n",(float)score/(float)counter);
			}
			//printf("<%f>\n",(float)score/(float)counter);
			// printf("movie id %d,counter %d score %d",find1leaf->movieID,counter,score);
		}
		printf("<%f>\n",(float)score/(float)counter);
	}else{
	return 0;
	}
	return 1;
}

/**
 * @brief Search for a movie with identification movieID in a specific category.
 *
 * @param movieID The identifier of the movie
 * @param category The category of the movie
 *
 * @return 0 on success
 *         1 on failure
 */

int search_movie(unsigned int movieID, int category)
{
	movie_t *tmp=categoryArray[category]->movie;
	centinel->movieID=movieID;

	while(tmp->movieID!=movieID){
		if(movieID>tmp->movieID){
			tmp=tmp->rc;
		}
		else if(movieID<tmp->movieID){
			tmp=tmp->lc;
		}
	}
	if(tmp==centinel){	
		return 0;
	}else{
			printf("I<%d><%d>\nDONE\n",tmp->movieID,tmp->year);
		return 1;
	}
	
}

/**
 * @brief Prints the movies in movies categories array.
 * @return 0 on success
 *         1 on failure
 */

int print_movies(void)
{
	printf("M\nMovie Category Array\n");
	printf("<category0>: ");
	categoryArray[0]->movie = maketreeT(m0, 0, m0i - 1);
	inorder_centinel(categoryArray[0]->movie);

	printf("\n<category1>: ");
	categoryArray[1]->movie = maketreeT(m1, 0, m1i - 1);
	inorder_centinel(categoryArray[1]->movie);

	printf("\n<category2>: ");
	categoryArray[2]->movie = maketreeT(m2, 0, m2i - 1);
	inorder_centinel(categoryArray[2]->movie);

	printf("\n<category3>: ");
	categoryArray[3]->movie = maketreeT(m3, 0, m3i - 1);
	inorder_centinel(categoryArray[3]->movie);

	printf("\n<category4>: ");
	categoryArray[4]->movie = maketreeT(m4, 0, m4i - 1);
	inorder_centinel(categoryArray[4]->movie);

	printf("\n<category5>: ");
	categoryArray[5]->movie = maketreeT(m5, 0, m5i - 1);
	inorder_centinel(categoryArray[5]->movie);
	printf("DONE\n");
	return 1;
}

/**
 * @brief Prints the users hashtable.
 * @return 0 on success
 *         1 on failure
 */

int print_users(void)
{
	/*printf("P\n");
	for(int i=0;i<hashtable_size;i++){
		user_t *tmp = user_hashtable_p[i];
		while (tmp)
	{
		user_t *userID=tmp->userID;
		printf("<%d>",tmp->userID);
		printf("History Tree:\n");
		inorderW(userID->history);
		
		tmp = tmp->next;
	}
	}*/
	return 1;
}
