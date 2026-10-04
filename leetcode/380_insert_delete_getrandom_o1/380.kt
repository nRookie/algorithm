class RandomizedSet {
    private val values = ArrayList<Int>()
    private val indices = HashMap<Int, Int>()

    fun insert(v: Int): Boolean {
        if (v in indices) return false

        indices[v] = values.size
        values.add(v)
        return true
    }

    fun remove(v: Int): Boolean {
        val removedIndex = indices[v] ?: return false
        val last = values.last()

        values[removedIndex] = last
        indices[last] = removedIndex

        indices.remove(v)
        values.removeAt(values.lastIndex)
        return true
    }

    fun getRandom(): Int = values.random()
}
