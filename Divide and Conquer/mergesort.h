#include <iostream>
#include <vector>

namespace userdefine_mergesort 
{
	template <typename T>
	class merge_sort
	{
		private:
			size_t size;
			std::vector<T> v;
			std::vector<T> sorted;

		public:
			merge_sort() { }

			merge_sort(int n)
			{
				v = std::vector<T>(n,0);
				size = static_cast<size_t>(v.size());
			}

			void SetArray(std::vector<T> input)
			{
				for(int i = 0; i < (int)input.size(); i++)
					v.push_back(input[i]);
				sorted = std::vector<T>(v.size(),0);
				size = v.size();
			}

			void mSort(int left,int right)
			{
				int mid;
				if(left < right)
				{
					mid = (left+right)/2;
					mSort(left,mid);
					mSort(mid+1,right);
					merge(left,right);
				}
			}

			void merge(int left,int right)
			{
				int mid = (left+right)/2;
				int i = left,j = mid+1,k = left;

				while(i <= mid && j <= right)
				{
					if(v[i] < v[j])
						sorted[k++] = v[i++];
					else
						sorted[k++] = v[j++];
				}

				while(i <= mid)
					sorted[k++] = v[i++];
				while(j <= right)
					sorted[k++] = v[j++];

				for(i = left; i <= right; i++)
					v[i] = sorted[i];
			}

			std::vector<T> GetArray(void)
			{
				return v;
			}

			size_t GetSize(void)
			{
				return size;
			}
	};
}
