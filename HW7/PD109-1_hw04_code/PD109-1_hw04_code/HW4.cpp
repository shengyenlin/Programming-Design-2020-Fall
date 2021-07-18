#include<iostream>
#include<cmath>
using namespace std;

/*PD 109-1 HW4*/



//Prob 1
/** ���D���:
����array�N�Ʀr��Ū�J�C
�B���Ƭݬݯ�_�R��Ҧ��Q�R�����C
�Y����A�a�|�q0��Q�R�����ƪ��Ҧ��զX�A
��X�i��Ѥ����̨θѡC
�̫��X���e�̨θ� **/


const int CUTOFF_NUM_MAX = 10;	//�̦h���X�ت��e 
const int TICKET_KIND = 2; 		//����������


// ���զX�O�_����ʶR 
bool isFeasibleToBuy(const int ticketNum[], const int intervalNum[], int budget,
	const int cutoffs[][CUTOFF_NUM_MAX], const int prices[][CUTOFF_NUM_MAX + 1]) {
	int needMoney = 0;	//�ʶR�һݪ��`�� 

	//��C�@�ز��A��X�`�� 
	for (int i = 0; i < TICKET_KIND; i++) {
		int ticketBought = 0;	//�������w�ʶR������
		//��C�ӰϬq�A���O�p����� 
		for (int j = 0; j < intervalNum[i]; j++) {
			if (ticketNum[i] >= cutoffs[i][j]) {	// case 1 ��ӰϬq�R��
				needMoney += prices[i][j] * (cutoffs[i][j] - ticketBought);
				ticketBought = cutoffs[i][j];
			}
			else {								// case 2 ���Ϭq�u�R���� 
				needMoney += prices[i][j] * (ticketNum[i] - ticketBought);
				ticketBought = ticketNum[i];
				break;
			}
		}
		if (ticketBought < ticketNum[i]) {	// �ݭn�R��̫�@�ӰϬq���� 
			needMoney += prices[i][intervalNum[i]] * (ticketNum[i] - ticketBought);
		}
	}
	return (needMoney <= budget);	//�^�ǬO�_�����R�� 
}


// ���զX�`�@�n��h�ֿ� 
int priceOf(const int ticketNum[], const int intervalNum[],
	const int cutoffs[][CUTOFF_NUM_MAX], const int prices[][CUTOFF_NUM_MAX + 1]) {
	int needMoney = 0;	//�ʶR�һݪ��`�� 

	//��C�@�ز��A��X�`�� 
	for (int i = 0; i < TICKET_KIND; i++) {
		int ticketBought = 0;	//�������w�ʶR������
		//��C�ӰϬq�A���O�p����� 
		for (int j = 0; j < intervalNum[i]; j++) {

			if (ticketNum[i] >= cutoffs[i][j]) {	// case 1 ��ӰϬq�R��
				needMoney += prices[i][j] * (cutoffs[i][j] - ticketBought);
				ticketBought = cutoffs[i][j];
			}
			else {								// case 2 ���Ϭq�u�R���� 
				needMoney += prices[i][j] * (ticketNum[i] - ticketBought);
				ticketBought = ticketNum[i];
				break;
			}
		}
		if (ticketBought < ticketNum[i]) {	// �ݭn�R��̫�@�ӰϬq���� 
			needMoney += prices[i][intervalNum[i]] * (ticketNum[i] - ticketBought);
		}
	}
	return needMoney;	//�^���`�� 
}


// �զXA�O�_�u����զXB
bool isBetter(const int ticketNum_A[], const int ticketNum_B[], const int buyingMod) {
	if (buyingMod == 1) {	// ���R�Ĥ@�ز��G��Ĥ@�ز��h���A�@�˪��ܿ�ĤG�ز��h�� 
		if (ticketNum_A[0] > ticketNum_B[0] ||
			(ticketNum_A[0] == ticketNum_B[0] && ticketNum_A[1] >= ticketNum_B[1])) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (buyingMod == 2) {	// ���R�ĤG�ز��G�M�W���ۤ� 
		if (ticketNum_A[1] > ticketNum_B[1] ||
			(ticketNum_A[1] == ticketNum_B[1] && ticketNum_A[0] >= ticketNum_B[0])) {
			return true;
		}
		else {
			return false;
		}
	}
	else {	// �����`���ơA�A�ݲ��ƭ��n�A�̫�ݲĤ@�ز����� 
		int totalTicket[2] = {
			ticketNum_A[0] + ticketNum_A[1],
			ticketNum_B[0] + ticketNum_B[1]
		};
		int ticketMultiply[2] = {
			ticketNum_A[0] * ticketNum_A[1],
			ticketNum_B[0] * ticketNum_B[1]
		};
		if ((totalTicket[0] > totalTicket[1]) ||
			(totalTicket[0] == totalTicket[1] && ticketMultiply[0] > ticketMultiply[1]) ||
			(totalTicket[0] == totalTicket[1] && ticketMultiply[0] == ticketMultiply[1] && ticketNum_A[0] > ticketNum_B[0])) {
			return true;
		}
		else {
			return false;
		}
	}
}



int main() {
	/* �ŧi�ܼ� */
	int intervalNumber[TICKET_KIND] = { 0 };	//�C�ز��϶��`��
	int ticketNumber[TICKET_KIND] = { 0 };	//�C�ز��ݭn�h��
	int totalBudget = 0;					//�`�w�� 
	int buyingMod = 0;						//�ʶR�Ҧ�
	int intervalCutoff[TICKET_KIND][CUTOFF_NUM_MAX] = { 0 };	 //�Ϭq���e 
	int intervalPrice[TICKET_KIND][CUTOFF_NUM_MAX + 1] = { 0 };//�Ϭq���� 


	/* Ū���ƭ� */
	for (int i = 0; i < TICKET_KIND; i++) {
		cin >> intervalNumber[i];		//Ū���Ϭq�� 
	}
	for (int i = 0; i < TICKET_KIND; i++) {
		cin >> ticketNumber[i];			//Ū�����ʶR���� 
	}
	cin >> totalBudget >> buyingMod;	//Ū���w��P�ʶR�Ҧ�	

	for (int i = 0; i < TICKET_KIND; i++) {	//Ū�����ƪ��e����
		for (int j = 0; j < intervalNumber[i]; j++) {
			cin >> intervalCutoff[i][j] >> intervalPrice[i][j];
		}
		cin >> intervalPrice[i][intervalNumber[i]];	//Ū���̫�@�q������ 
	}



	/* �Y�i�H�R���A�������� */
	if (isFeasibleToBuy(ticketNumber, intervalNumber, totalBudget, intervalCutoff, intervalPrice)) {
		for (int i = 0; i < TICKET_KIND; i++) {
			cout << ticketNumber[i] << ",";
		}
		cout << priceOf(ticketNumber, intervalNumber, intervalCutoff, intervalPrice);
		return 1;
	}



	/* �a�|�Ҧ��i�઺���ƲզX */
	int bestTicketNow[TICKET_KIND] = { 0 };	//���e�̨θ�
	for (int i = 0; i <= ticketNumber[0]; i++) {		// i: �Ĥ@�ز����ƶq 
		for (int j = 0; j <= ticketNumber[1]; j++) {	// j: �ĤG�ز����ƶq 
			int ticketTry[TICKET_KIND] = { i, j };
			// �p�G�����եi��A�B����e�̨θѧ�n�A�N��s 
			if (isFeasibleToBuy(ticketTry, intervalNumber, totalBudget, intervalCutoff, intervalPrice)
				&& isBetter(ticketTry, bestTicketNow, buyingMod)) {
				bestTicketNow[0] = ticketTry[0];
				bestTicketNow[1] = ticketTry[1];
			}
		}
	}



	/* ��X�`�� */
	for (int i = 0; i < TICKET_KIND; i++) {
		cout << bestTicketNow[i] << ',';
	}
	cout << priceOf(bestTicketNow, intervalNumber, intervalCutoff, intervalPrice);

	return 0;
}






//// Problem 2  Moving average
//float MAPE(int windowSize , int periodCut , const int sales[]){
//	float MAPE = 0;
//	// ���i����MA
//	for(int i = windowSize; i < periodCut; i++){
//		float x = float(sales[i]);	// x = ��i����ڭ�
//		 
//		// �^��j���A�D��i�����w����(f)
//		float f = 0;
//		for(int j=1; j <= windowSize; j++){
//			f += sales[i-j];
//		} 
//		f /= windowSize;
//		
//		// ����MAE = (��ڭ�-���p��) / ��ڭ�
//		float MAE = abs(x - f) / x;
//		
//		// �[�JMAPE 
//		MAPE += MAE;
//	}
//	MAPE /= float(periodCut - windowSize);	//��MAPE������ 
//	return MAPE;
//}
//
//int main(){
//	/* ��J */ 
//	int period = 0;	//�`���v��ƴ��� 
//	cin >> period; 
//	int data[period] = {0};
//	for(int i=0; i<period; i++){
//		cin >> data[i];
//	}
//	
//	/* �պ�C�عw�����ƪ�MAPE */
//	int maxMAPE = 9999;	//�̾��D�ح����XMAPE�̤j��9999 
//	int bestMAPE = maxMAPE + 1;	// ���e�̨�MAPE(%����)
//	// bestMAPE �w�]���D�N���i�઺�̤j��+1�A�Y|10000 - 1| / 1 + 1 
//	int bestWindow = -1;
//	for(int n=2; n<=6; n++){	// n = window size
//		int newMAPE = int(MAPE(n, period, data) * 100.0);
//		// �Y���o��p��MAPE�A�N��s 
//		cout << newMAPE<<endl;
//		if(newMAPE < bestMAPE){
//			bestWindow = n;
//			bestMAPE = newMAPE;
//		}
//	}
//	
//	cout << bestWindow << "," << bestMAPE;
//	
//	return 0;
//}






//// Problem 3 Airport Location
//int LOCATION_NUM = 0;
//
//// revenue(): ���w�@�ոѡA�D��b�Q(�Q���`�X-�سy����) 
//int revenue(const bool solution[], const int cost[], int* const profit[]){
//	int answer = 0;	//�N�n��X���`�Q��
//	
//	//�⦨��
//	for(int i = 0; i < LOCATION_NUM; i++){	
//		answer -= cost[i] * solution[i];		
//	}
//	
//	//��Q���]���e��L��������^
//	for(int i = 0; i < LOCATION_NUM - 1; i++){	 
//		for(int j = i + 1; j < LOCATION_NUM; j++){
//			answer += profit[i][j - i - 1] * solution[i] * solution[j]; 
//		}		
//	}
//	
//	return answer;
//}
//
//int main(){
//	/* ��J */
//	cin >> LOCATION_NUM;
//	int cost[LOCATION_NUM] = {0};			//�سy����  
//	for(int i = 0; i < LOCATION_NUM; i++){
//		cin >> cost[i];
//	}
//	//�B�z�u���@�Ӿ������S�� 
//	if(LOCATION_NUM == 1){
//		cout << "0;0";
//		return 0;
//	}
//	
//	int* benifit[LOCATION_NUM - 1] = {0};	//��u�Q��
//	for(int i = 0; i < LOCATION_NUM - 1; i++){
//		benifit[i] = new int[LOCATION_NUM - i - 1] {0};
//		for(int j = i + 1; j < LOCATION_NUM; j++){
//			cin >> benifit[i][j - i - 1];	//��array�ܦ��ˤT���A�`���x�s�Ŷ� 
//		}
//	}
//	
//	
//	
//	/* ���ƧR�������A����L�k�W�i�Q�� */
//	bool build[LOCATION_NUM] = {0};		//���e����
//	bool newAnswer[LOCATION_NUM] = {0};	//���դ����s�@�ո�
//	for(int i = 0; i < LOCATION_NUM; i++){	//�w�]�����\��
//		build[i] = 1;
//		newAnswer[i] = 1;
//	}
//	int revenueNow = revenue(build, cost, benifit);
//	bool change = true;	//�e�@�����S���W�i�įq
//	 
//	//�e�@�����W�i�Q���A�N�~�����G 
//	while(change){
//		change = false;		//���m���L�i�B���X�� 
//		int remove = -1;	//�o���n������������index 
//		//���C�ӵ��פ��i�H�m������ 
//		for(int i = 0; i < LOCATION_NUM; i++){
//			//�w�g�S�����N���L��
//			if(!build[i]){ 
//				continue;
//			}
//			
//			//�������A�h�յ۩��
//			newAnswer[i] = false;			 
//			int newRevenue = revenue(newAnswer, cost, benifit);
//			if(newRevenue > revenueNow){ //�Y���Q���W�ɡA�h��s	 
//				remove = i;	//��s�n�����index 
//				revenueNow = newRevenue;
//				change = true;				
//			}
////			cout<<"here "<<i<<", old="<<revenueNow<<", new="<<newRevenue<<endl;
//			newAnswer[i] = true;	//���_��A�~����թ�t�@�� 
//		} 
//		if(change){	//���ﵽ���ܡA���ﵽ�̤j�����Ӿ��� 
//			build[remove] = false;
//			newAnswer[remove] = false;
////			cout<<"real remove "<<remove<<", revenue="<<revenueNow<<endl; 
//		}		
//	} 
//	
//	/* ��X */
//	cout << build[0];
//	for(int i = 1; i < LOCATION_NUM; i++){
//		cout << "," << build[i];
//	}
//	cout << ";" << revenueNow;
//	return 0;
//}








