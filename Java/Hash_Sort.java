import java.util.*;

public class Hash_Sort {
    public static void hashSort(List<Integer> arr) {
        Map<Integer, Integer> hashTable = new HashMap<>();
        int maxVal = 0;

        for (int num : arr) {
            hashTable.put(num, hashTable.getOrDefault(num, 0) + 1);
            if (num > maxVal) maxVal = num;
        }

        arr.clear();
        for (int i = 0; i <= maxVal; i++) {
            if (hashTable.containsKey(i)) {
                for (int j = 0; j < hashTable.get(i); j++)
                    arr.add(i);
            }
        }
    }

    public static void main(String[] args) {
        List<Integer> arr = new ArrayList<>(Arrays.asList(4, 2, 2, 8, 3, 3, 1));

        System.out.println("Arreglo original: " + arr);

        hashSort(arr);

        System.out.println("Arreglo ordenado: " + arr);
    }
}